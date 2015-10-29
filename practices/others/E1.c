#include <math.h>
#include <stdlib.h>
#include <stdio.h>


double ode(double t, double y) 
{
  

return y;
}

double fwd_euler(double(*fn)(double t, double y), double t, double y, double h)
{


return y+h*fn(t,y); 
}

double back_euler(double(*fn)(double t, double y), double t, double y, double h)
{


return  y/(1-h); 
}

double centraldifference(double(*fn)(double t, double y), double t, double y, double h)
{


return  y+h*fn(t+0.5,y+0.5*h*fn(t,y)); 
}


double rk4(double(*fn)(double t, double y), double t, double y, double h)
{
double k[4];
k[0]=fn(t,y);
k[1]=fn(t+0.5*h,y+0.5*h*k[0]);
k[2]=fn(t+0.5*h,y+0.5*h*k[1]);
k[3]=fn(t+h,y+h*k[2]);

return  y+h*(k[0]+2.0*k[1]+2.0*k[2]+k[3]/6.0); 
}

int main (int argc, char *argv[])
{
double y, y_new, y_exact, t, h, err;
double t_end =1.0;
y=1.0; t=0.0; 

h=atof(argv[1]);

while (t< t_end)
{
y_new=rk4(ode,t,y,h);
t=t+h;y=y_new; y_exact=exp (t);
printf("t=%f, y=%f, y_exact=%f\n", t,y,y_exact);
}

printf("y(1)=%f\n",y);
return 0;
}








