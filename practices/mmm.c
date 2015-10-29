


/* MPI_INT
   MPI_FLOAT*/


#include<stdio.h>

#include<mpi.h>



int main(int argc,char *argv[]) {

int np,rank,partner;

MPI_Status get;

MPI_Init(&argc, &argv);

MPI_Comm_size(MPI_COMM_WORLD,&np);

MPI_Comm_rank(MPI_COMM_WORLD, &rank);

/* MPI_send  (void *data, int count, MPI_Datatype datatype, 
int destenation, int tag=1, MPI_Comm communicator) 

 MPI_Recv(",",",int Source, ",", MPI_Status *status); */

if (rank<np/2){

partner=np/2+rank;

MPI_Send(&rank, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);

}
else
{

MPI_Recv(&partner,1,MPI_INT,MPI_ANY_SOURCE, 1, MPI_COMM_WORLD,&get);

}




printf("Process %d is partner of process %d\n",rank,partner);





MPI_Finalize();
return 0;

}

