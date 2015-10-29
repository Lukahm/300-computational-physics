


/* MPI_INT
   MPI_FLOAT*/


#include<stdio.h>

#include<mpi.h>



int main(int argc,char *argv[]) {

int np,rank,get,partner;



MPI_Init(&argc, &argv);


/* MPI_send  (void *data, int count, MPI_Datatype datatype, 
int destenation, int tag=1, MPI_Comm communicator) */


MPI_send  (&rank, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);

/* MPI_Recv(",",",int Source, ",", MPI_Status *status); */




MPI_Recv(&rank,1,MPI_INT,int Source, 1, MPI_get);

MPI_ANY_SOURCE

if(partner==np/2) {


printf("Process %d is partner of process %d\n",rank,partner);

}



MPI_Finalize();
return 0;

}


