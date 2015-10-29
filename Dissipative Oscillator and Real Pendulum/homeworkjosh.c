#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// The array of ODE

void ode(double t, double yz[], double dyz[], double w0, double beta)
{
dyz[0] = yz[1];
dyz[1] =-2*beta*yz[1]- w0*w0* yz[0];
}

//The Runge-Kutta calculation 
void rk4(double t, double yz[], double h, double w0, double beta)
{
double k[4][2], dyz[2], yzn[2];
int j;
 ode(t,yz,dyz,w0,beta);

for(j=0; j<2; j++)
{k[0][j]=h*dyz[j];
yzn[j]=yz[j]+0.5*h*k[0][j];}
ode(t+0.5*h, yzn, dyz, w0,beta);

for(j=0;j<2;j++)
{k[1][j]=h*dyz[j];
yzn[j]=yz[j]+0.5*h*k[1][j];}
ode(t+0.5*h, yzn, dyz, w0,beta);

for(j=0;j<2;j++)
{k[2][j]=h*dyz[j];
yzn[j]=yz[j]+0.5*h*k[2][j];}
ode(t+0.5*h, yzn, dyz, w0,beta);

for(j=0;j<2;j++)
{k[3][j]=h*dyz[j];
yzn[j]=yz[j]+0.5*h*k[3][j];}

for(j=0;j<2;j++)
  {yz[j]=yz[j]+(k[0][j] + 2*k[1][j] + 2*k[2][j] +k[3][j])/6.0;
}
}

//Initialization of parameters and function of output test file

int main(void){
  double t, h, y[2], w0, beta;
  t=0.0;
  h=0.01;
  y[0]=1.0;
  y[1]=0.0;
  FILE *fid;
  fid=fopen("test.dat","w");
    fprintf(fid,"%f \t %f \n", t, y[0]);
    printf("beta:\n");
    scanf("%lf",&beta);
    printf("w0:\n");
    scanf("%lf",&w0);
  while(t<10.0)
    {rk4(t,y,h,w0,beta);
      t=t+h;
      fprintf(fid, "%f \t %f\n",t,y[0]);
    }
  fclose(fid);
  return 0;
}

