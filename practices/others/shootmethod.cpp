#include "cptstd.hpp"
#include "basalg.hpp"
#include "diffeq.hpp"
using namespace cpt;

const double pi = 4 * atan(1.0);

double x_lb = 0;                    // left boundary point
double x_rb = 1;                    // right boundary point
double u_lb = 0;                    // boundary condition at x = 0
double u_rb = 1;                    // boundary condition at x = 1
double delta = 1;                   // guess for u'(0)

enum extended_space { _x, _u, _dudx, dimension };

Matrix<double,1> p(dimension);      // point in extended space
#include "cptstd.hpp"
#include "basalg.hpp"
#include "diffeq.hpp"
using namespace cpt;

const double pi = 4 * atan(1.0);

double x_lb = 0;                    // left boundary point
double x_rb = 1;                    // right boundary point
double u_lb = 0;                    // boundary condition at x = 0
double u_rb = 1;                    // boundary condition at x = 1
double delta = 1;                   // guess for u'(0)

enum extended_space { _x, _u, _dudx, dimension };

Matrix<double,1> p(dimension);      // point in extended space

void set_initial_values()
{
    p[_x] = x_lb;
    p[_u] = u_lb;
    p[_dudx] = delta;
}

int N = 100;                        // number of integration steps
double dx = (x_rb - x_lb) / N;      // Runge-Kutta step size

Matrix<double,1> flow(              // derivative vector for Runge-Kutta
    Matrix<double,1>& p)
{
    double x = p[_x], u = p[_u], dudx = p[_dudx];
    Matrix<double,1> f(dimension);
    f[_x] = 1;
    f[_u] = dudx;
    f[_dudx] = - pi * pi * (u + 1) / 4;
    return f;
}

double F(double x)                  // function whose root is to be found
{
    delta = x;                      // set global delta for root finding
    set_initial_values();           // in global extended point p
    for (int i = 0; i < N; i++)     // integrate from x_lb to x_rb
        RK4_step(p, dx, flow);      // using 4th order Runge-Kutta
    double u = p[_u];               // solution at right boundary
    return u - u_rb;                // mismatch in right boundary value
}

int main() {
    cout << " Shooting solution of u'' = - pi^2 (u+1) / 4\n"
         << " with boundary conditions u(0) = 0, u(1) = 1\n";
    delta = (u_rb - u_lb) / (x_rb - x_lb);
    cout << " using initial guess delta = " << delta << endl;

    SecantSearch ss;                // Secant search object
    ss.set_first_root_estimate(delta);
    ss.set_second_root_estimate(delta + dx);
    ss.print_steps();               // root finder will print each step
    delta = ss.find_root(F);
    cout << "\n Secant search found delta = " << delta << endl;

    set_initial_values();           // to integrate the final solution
    ofstream data_file("shoot.data");
    data_file << p[_x] << '\t' << p[_u] << '\t' << p[_dudx] << '\n';

    for (int i = 0; i < N; i++) {
        RK4_step(p, dx, flow);      // take one Runge-Kutta step
        data_file << p[_x] << '\t' << p[_u] << '\t' << p[_dudx] << '\n';
    }
    data_file.close();
    cout << "\n " << N << " step solution in file shooting.data"
         << endl;
}

void set_initial_values()
{
    p[_x] = x_lb;
    p[_u] = u_lb;
    p[_dudx] = delta;
}

int N = 100;                        // number of integration steps
double dx = (x_rb - x_lb) / N;      // Runge-Kutta step size

Matrix<double,1> flow(              // derivative vector for Runge-Kutta
    Matrix<double,1>& p)
{
    double x = p[_x], u = p[_u], dudx = p[_dudx];
    Matrix<double,1> f(dimension);
    f[_x] = 1;
    f[_u] = dudx;
    f[_dudx] = - pi * pi * (u + 1) / 4;
    return f;
}

double F(double x)                  // function whose root is to be found
{
    delta = x;                      // set global delta for root finding
    set_initial_values();           // in global extended point p
    for (int i = 0; i < N; i++)     // integrate from x_lb to x_rb
        RK4_step(p, dx, flow);      // using 4th order Runge-Kutta
    double u = p[_u];               // solution at right boundary
    return u - u_rb;                // mismatch in right boundary value
}

int main() {
    cout << " Shooting solution of u'' = - pi^2 (u+1) / 4\n"
         << " with boundary conditions u(0) = 0, u(1) = 1\n";
    delta = (u_rb - u_lb) / (x_rb - x_lb);
    cout << " using initial guess delta = " << delta << endl;

    SecantSearch ss;                // Secant search object
    ss.set_first_root_estimate(delta);
    ss.set_second_root_estimate(delta + dx);
    ss.print_steps();               // root finder will print each step
    delta = ss.find_root(F);
    cout << "\n Secant search found delta = " << delta << endl;

    set_initial_values();           // to integrate the final solution
    ofstream data_file("shoot.data");
    data_file << p[_x] << '\t' << p[_u] << '\t' << p[_dudx] << '\n';

    for (int i = 0; i < N; i++) {
        RK4_step(p, dx, flow);      // take one Runge-Kutta step
        data_file << p[_x] << '\t' << p[_u] << '\t' << p[_dudx] << '\n';
    }
    data_file.close();
    cout << "\n " << N << " step solution in file shooting.data"
         << endl;
}
 



