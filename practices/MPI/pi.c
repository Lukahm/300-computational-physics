#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 

int M=1000000;
int I=0;
int xi;
float x,y;
float result;

int main(void) {

	srand(time(NULL)); 

	for (xi=0;xi<M;xi++){

		x=rand()*1.0/RAND_MAX;
		y=rand()*1.0/RAND_MAX;
		
//		if(  pow((pow(x,2)+pow(y,2)),0.5)  ) {
		if(  sqrt( pow(x,2) + pow(y,2) ) <1.0 ) {
			I+=1;

		}
	}

result=4.0*I/xi;

printf("%f\n",result); 



}  
