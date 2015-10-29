#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int **Spins;
int L;
int evaluatehamiltonian();

#include "hamiltonian.c"

int main(void){

	
double beta = 0.25;
L=10;

int xi, x,y, i,j;
int N = L*L;
int Nrows = L;
int Ncols = L;

int M = 50000;
int nb=5;

int H1,H2;
	

//Initialize radom number generator with system time;	
srand(time(NULL));


// Spins Allocation
	

Spins = malloc(Nrows * sizeof(int *));	
	
if ( Spins == NULL )
{
	fprintf(stderr,"OUT OF MEMORY!\n");
}


for(x = 0; x < Nrows; x++)
{
	Spins[x] = malloc(Ncols * sizeof(int));
	
	if (Spins[x] == NULL )
	{
		fprintf(stderr,"OUT OF MEMORY!\n");
	 
	}
}



//Initialize spins

for(x = 0; x < Nrows; x++)	
{
       for(y = 0; y < Ncols; y++)
        {
		Spins[x][y]=1;
	}
}




double *averageh;
averageh=malloc(nb*sizeof(double));

for(i=0;i<=nb; i++){
averageh[i]=0;
}

int n;
for (n=-1;n<nb;++n) {

	for (xi = 0; xi <M; xi++)
	{
		H1=evaluatehamiltonian();
		
		x = (double)floor(rand()*1.0*L/RAND_MAX);
		y = (double)floor(rand()*1.0*L/RAND_MAX);
		Spins[x][y]=(-1)*Spins[x][y];
		
		H2=evaluatehamiltonian();
		if (H2<=H1) {
			
		}
		
		
		
		if (H2 > H1){
			double U =  rand()*1.0/RAND_MAX;	
			if ( U < exp(-beta*(H2-H1)) ) 
			{
				// accepting the trail configuration
			}

			else 
			{
				Spins[x][y]=(-1)*Spins[x][y];
				
			}
		}

               if(n>-1){    		
		averageh[n] += 1.00*evaluatehamiltonian();
               }
	}

	averageh[n] /= M;
	fprintf(stdout,"+++++++++++++ %f\n",averageh[n]);

}
		


	





	
}



