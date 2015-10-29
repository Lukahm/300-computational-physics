
#include<stdio.h>

#include<mpi.h>



int main(int argc,char *argv[]) {

int i,np,rank;
float x,y;

int I=0;



MPI_Init(&argc, &argv);

MPI_Comm_size(MPI_COMM_WORLD,&np);

MPI_Comm_rank(MPI_COMM_WORLD, &rank);

srand(time(NULL)); 

for(i=0;i<np;i++) {

		x=rand()*1.0/RAND_MAX;
		y=rand()*1.0/RAND_MAX;
		
//		if(  pow((pow(x,2)+pow(y,2)),0.5)  ) {
		if(  sqrt( pow(x,2) + pow(y,2) ) <1.0 ) {
			I+=1;

		}

}

result=4.0*I/i;


if (rank<np/2){

partner=np/2+rank;

MPI_Send(&rank, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);

}
else
{

MPI_Recv(&partner,1,MPI_INT,MPI_ANY_SOURCE, 1, MPI_COMM_WORLD,&get);

}

printf("Process %d is partner of process %d\n",rank,partner)


MPI_Finalize();
return 0;

}


