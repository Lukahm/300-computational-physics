#include<stdio.h>
#include <stdlib.h>







int main(int argc, char *argv[]){



const int ndim=4;
	int ndim2;

ndim2=ndim*ndim;

float x,y,z;
float *mat1,*mat2,*mat3;


int i,j,k,l,m;



//Allocate memory x y z
	x=mat1;
	y=mat2;
	z=mat3;

	mat1=malloc(sizeof(float)*4);
	mat2=malloc(sizeof(float)*4);
	mat3=malloc(sizeof(float)*4);

	mat1[0]=0;
	mat2[0]=1;
	
	for(i=0;i<16;i++)
	{
	mat1[i+1]+=mat1[i];
	}
	
	
	for(i=0;i<16;i++)
	{
	mat2[i]+=mat2[i+1];
	}




//initialize

int n=0;

for(i=0;i<ndim;i++){


	for(j=0;j<ndim;j++){

		for(k=0;k<ndim;k++){
			l=coord(i,k,ndim);
			m=coord(k,j,ndim);
			z[n]+=x[l]*y[m];

		}
	n++;
	}
	
}


printf("%s\n",z[n]);

}




int coord(int i, int j, int nj){

return j+i=nj;


}
