#include <stdio.h>
#include <math.h>
#define p1(y1,y2,t) (y2)
#define p2(y1,y2,t) (-y1)
double pi;

int main()
	/* This program is written for boundary value problem with the shooting
   method(includes the Runge-Kutta and secant methods).*/
	
{
int i,n;
double dl=1e-6;
double dk11,dk21,dk12,dk22,dk13,dk23,dk14,dk24;
double x,xl,xu,dx,h,yl,yu,x0,x1,x2,d,y1,y2,f0,f1;
double y[2][100];
extern double pi;

/* Initialization of the oscillator */
 
n = 100;
d = 0.1;
pi = 4*atan(1);
xl = -10;
xu = 10;
h  = (xu-xl)/(n-1);
yl = 0;  // y(0)=0
yu = 2;  // y(pi/2)=2  
x0 = (yu-yl)/(xu-xl);
dx = 0.01;
x1 = x0+dx;
y[0][0] = yl;

/* The root can be found by secant research. */

while (fabs(d) > dl)
  {
/* The Runge-Kutta calculation of the first trial solution */

  y[1][0] = x0;
  for (i = 0; i < n-1; ++i)
    {
    x = xl+h*(i+1);
    y1 = y[0][i];
    y2 = y[1][i];
    dk11 = h*p1(y1,y2,x);
    dk21 = h*p2(y1,y2,x);
    dk12 = h*p1((y1+dk11/2),(y2+dk21/2),(x+h/2));
    dk22 = h*p2((y1+dk11/2),(y2+dk21/2),(x+h/2));
    dk13 = h*p1((y1+dk12/2),(y2+dk22/2),(x+h/2));
    dk23 = h*p2((y1+dk12/2),(y2+dk22/2),(x+h/2));
    dk14 = h*p1((y1+dk13),(y2+dk23),(x+h));
    dk24 = h*p2((y1+dk13),(y2+dk23),(x+h));
    y[0][i+1] = y[0][i]+(dk11+2*(dk12+dk13)+dk14)/6;
    y[1][i+1] = y[1][i]+(dk21+2*(dk22+dk23)+dk24)/6;
    }
  f0 = y[0][n-1]-1;

/* Runge-Kutta calculation of the second trial solution */

  y[1][0] = x1;
  for (i = 0; i < n-1; ++i)
    {
    x = xl+h*(i+1);
    y1 = y[0][i];
    y2 = y[1][i];
    dk11 = h*p1(y1,y2,x);
    dk21 = h*p2(y1,y2,x);
    dk12 = h*p1((y1+dk11/2),(y2+dk21/2),(x+h/2));
    dk22 = h*p2((y1+dk11/2),(y2+dk21/2),(x+h/2));
    dk13 = h*p1((y1+dk12/2),(y2+dk22/2),(x+h/2));
    dk23 = h*p2((y1+dk12/2),(y2+dk22/2),(x+h/2));
    dk14 = h*p1((y1+dk13),(y2+dk23),(x+h));
    dk24 = h*p2((y1+dk13),(y2+dk23),(x+h));
    y[0][i+1] = y[0][i]+(dk11+2*(dk12+dk13)+dk14)/6;
    y[1][i+1] = y[1][i]+(dk21+2*(dk22+dk23)+dk24)/6;
    }
  f1 = y[0][n-1]-1;
  d = f1-f0;
  x2 = x1-f1*(x1-x0)/d;
  x0 = x1;
  x1 = x2;
  }
for (i = 0; i < n; ++i)
  {
  x = h*i;
  printf("%16.8lf %16.8lf\n", x,y[0][i]);
	}
	
}