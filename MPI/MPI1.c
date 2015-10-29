#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include <mpi.h>


int L=8;
int *Spins;
int evaluatehamiltonian();
  

#include "Hamiltonian1.c"



int main(int argc, char *argv[]){
	
//8 processors

	
int my_rank;
int portion=4;
int np=2;
int sites;
MPI_Status status;
	
int *newarray;

double beta = 0.1;
 

long int xi, x;

int M = 5;

int H1,H2;

//int ip;//counter for processors  
int is;//counter for spins

	
	
  /* Usual MPI startup stuff */
 MPI_Init(&argc, &argv);
 MPI_Comm_size(MPI_COMM_WORLD, &np);
 MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);



//Initialize radom number generator with system time;	
srand(time(NULL));
		


// Spins Allocation



if(my_rank==0){

Spins = malloc(sizeof(int)*L);	


for(x = 0; x < L; x++)	
{
Spins[x]=1;
	
}

}
newarray=malloc(sizeof(int)*(portion+2));						

			
//Initialize spins





if(my_rank==0){


//Data for processor 0	
					
	for(is=1;is<=portion;is++)
	{
	newarray[is]=Spins[is-1];
	}

newarray[0]=Spins[L-1];//PBC


newarray[portion+1]=Spins[portion];

}



					
/* MPI_send  (void *data, int count, MPI_Datatype datatype,int destenation, int tag=1, MPI_Comm communicator) 

 MPI_Recv(",",",int Source, ",", MPI_Status *status); */




if (my_rank==0)
{
		
MPI_Send(&Spins[4], 4, MPI_INT, 1, 1, MPI_COMM_WORLD);
		

}

if (my_rank==1) {MPI_Recv(&newarray[1],4,MPI_INT,MPI_ANY_SOURCE, 1, MPI_COMM_WORLD,&status);}


if (my_rank==0)
{
		
MPI_Send(&Spins[3], 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		

}if (my_rank==1) {MPI_Recv(&newarray[0],1,MPI_INT,MPI_ANY_SOURCE, 1, MPI_COMM_WORLD,&status);}


if (my_rank==0)
{
		
MPI_Send(&Spins[0], 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		

}if (my_rank==1) {MPI_Recv(&newarray[5],1,MPI_INT,MPI_ANY_SOURCE, 1, MPI_COMM_WORLD,&status);}


printf("%d",Spins[x]);


for (xi = 0; xi <M; xi++)   
{
//even	
	for(sites=1;sites<=portion;sites+=2)
	{

		H1=evaluatehamiltonian(x);
									

		Spins[x]=(-1)*Spins[x];
									
		H2=evaluatehamiltonian(x);
								
				if (H2<=H1) {
			
		                 }
							
									
									
					if (H2 > H1)
					{
			                double U =  rand()*1.0/RAND_MAX;	
							if ( U < exp(-beta*(H2-H1)) ) 
							{
						// accepting the trail configuration
							}

							else 
							{
							Spins[x]=(-1)*Spins[x];
											
							}
					}
	}
//Communication newarray[]
if (my_rank==0)
{
		
MPI_Send(&newarray[2], 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		

}if (my_rank==1) {MPI_Recv(&newarray[5],1,MPI_INT,MPI_ANY_SOURCE, 1, MPI_COMM_WORLD,&status);}


if (my_rank==1)
{
		
MPI_Send(&newarray[1], 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		

}if (my_rank==0) {MPI_Recv(&newarray[5],1,MPI_INT,MPI_ANY_SOURCE, 1, MPI_COMM_WORLD,&status);}
  


				
				//odd
				for(sites=2;sites<=portion;sites+=2)
				{

				H1=evaluatehamiltonian(x);
								
				Spins[x]=(-1)*Spins[x];
									
				H2=evaluatehamiltonian(x);
									
									
						if (H2<=H1) {
			
		                                }
					
						if (H2 > H1)
						{
			                        double U =  rand()*1.0/RAND_MAX;	

							if ( U < exp(-beta*(H2-H1)) ) 
							{
						// accepting the trail configuration
							}
							else 
							{
							Spins[x]=(-1)*Spins[x];
						    }
						} 
									
				}

		
			
//Communication newarray[]
if (my_rank==0)
{
		
MPI_Send(&newarray[2], 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		

}if (my_rank==1) {MPI_Recv(&newarray[5],1,MPI_INT,MPI_ANY_SOURCE, 1, MPI_COMM_WORLD,&status);}


if (my_rank==1)
{
		
MPI_Send(&newarray[1], 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		

}if (my_rank==0){MPI_Recv(&newarray[5],1,MPI_INT,MPI_ANY_SOURCE, 1, MPI_COMM_WORLD,&status);}
			

}






printf("%d",Spins[x]);


  MPI_Finalize();

  return 0;

}
