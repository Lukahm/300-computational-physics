#include <math.h>
#include <stdio.h>

int main() { int i,N;
             float x;
             float from,to;
             float inc; float diff; float deriv; 
             float a[4]; float cubic(float a[4], float x);
             float asymm( float (*fn) (float *a,float x),
                          float *a, float x, float diff);
             

             
from=0; to=10; diff=0.1; N=20; 
a[0]=1,a[1]=1,a[2]=-10,a[3]=1;
             inc= (to-from)/N; x=from;

for (i=0; i<N; i++ ) {

deriv=(asymm(cubic, a, x, diff));
printf("%f %f\n", x, deriv);

x+=inc;

}

return 0;
                  
}

float asymm( float (*fn) (float *a,float x), float *a, float x, float diff)
             

{

return (fn (a,x+diff) - fn (a,x))/diff;
}


float cubic(float a[4], float x){
	return a[0] + a[1]*x + a[2]*pow(x,2) + a[3]*pow(x,3);
}


 
