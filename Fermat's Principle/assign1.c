// This program is written by Haomin Liu 12109377
//Assignment 1: Fermat's Principle 

#include <stdio.h>
#include <math.h>


int main (void) {
	
	float c;
	float x[3],y[3],n[2],velocity[2],time[2],dist[2];
	float d1(float x[3],float y[3]), d2(float x[3],float y[3]);
	float diff1(float d1, float x[3],float velocity[2]), diff2(float d2, float x[3], float velocity[2]);
	float diff,step,change;
	float z, t;
	int i,N;
	
	c = 1.0;
	y[2]=0;
	
//In order to determine the travel time as a function of x3(the point on x-axis), the following statements will load the initial values which are given conditions for the problem.
	
	printf("Enter the value of initial coordinate(x0,y0)):\n");
	scanf("%f,%f",&x[0],&y[0]);
	printf("Enter the value of final coordinate(x1,y1):\n ");
	scanf("%f,%f",&x[1],&y[1]);
	printf("Enter the refractive index of the initial medium :\n");
	scanf("%f",&n[0]);
	printf("Enter the refractive index of the final medium :\n");
	scanf("%f",&n[1]);



//The following equations are used to calculate the speed of light in a medium, travel distance and travel time.

	velocity[0]=(c/n[0]);
	velocity[1]=(c/n[1]);
	
	dist[0]=sqrt(pow((x[0]-x[2]),2)+pow(y[0],2));
	dist[1]=sqrt(pow((x[1]-x[2]),2)+pow(y[1],2));
	
	time[0]=dist[0]/velocity[0];
	time[1]=dist[1]/velocity[1];
	
	
	// From now on, steepest descent method will be used to minimise the function and therefore find x3. 

	/* Max number of iterations */
	N=100;
	
	/* Initial parameters */
	step=0.2;
	x[2]=-5.0;
	

	for(i=0; i<N; i++){
		
		diff=diff1(dist[0],x,velocity)+diff2(dist[1],x,velocity);

		printf("Differential=%f\n",diff);
		
		z=x[2]-step*diff;
		printf("New min at x[3]=%f\n",z);
	
		change=fabs(x[2]-z);
		printf("change=%f\n\n",change);
		
		if(change<1e-5){
			printf("Converged.\n"); 
			break;
		}
		
		x[2]=z;
	}
	
//Finally, the useful output infomation speed,intersection point on x-axis and the travel time shows as following
	
	printf("The velocity in the initial medium is %f km/s \n",velocity[0]);
	
	printf("The velocity in the final medium is %f km/s \n",velocity[1]);
	
	printf("The intersection point on x-axis is %f\n",x[2]);
	
	t= dist[0]/ velocity[0] + dist[1]/velocity[1] ;
	
	printf("The travel time as a function of x3 is %f seconds \n",t);

} 

//Function definition: Differential equations

	float diff1(float d1, float x[3],float velocity[2]){
		return (-0.5)*(pow(d1,-0.5))*2.0*(x[0]-x[2])/velocity[0];
	}
	float diff2(float d2, float x[3], float velocity[2]){
		return (-0.5)*(pow(d2,-0.5))*2.0*(x[1]-x[2])/velocity[1];
	}

//Function definition: Distance of the light ray traveled 

	float d1(float x[3],float y[3]){
		float j,k;
		k=(x[2]-x[0]);
		j=y[0];
		return sqrt(pow(k,2)+pow(j,2));
	}
	float d2(float x[3],float y[3]){
		float o,s;
		o=(x[2]-x[1]);
		s=y[2];
		return sqrt(pow(o,2)+pow(s,2));
	}
	
//Comment on the suitability of this method and on the strengths and weaknesses of the code.

	
/*
	Suitability:
	
	1.The steepest decent method is also called gradient descent. it is a model to estimate minimum deviation.
	The speed of convergence is relatively slow when data close to minimum.
	
	2.Its asymptotic rate of convergence is inferior to many other methods
	
	3.Gradient methods are ill-defined for non-differentiable functions, but in this problem gradient method is a suitable way to find minimum. 
	

	
	The strengths and weaknesses of the code:
	
	Pros:
	1.Clear indentation and decleration makes the code more readable.
	
	2.Clear and simple logic sequence.
	
	3.Sub functions are used for easy debugging. 
	
	
	Cons:
	1.loops and functions can be simpler.

   2.logic sequence can be more clear.
	
	3.arrays and strings were not used efficiently. 
	
	
	*/
	
	