
#include<stdio.h>

#include<mpi.h>



int main(int argc,char *argv[]) {

int np,rank,len;

char myname[20];



MPI_Init(&argc, &argv);

MPI_Comm_size(MPI_COMM_WORLD,&np);

MPI_Comm_rank(MPI_COMM_WORLD, &rank);

if (rank == 0){

printf("hello world\n");

}

MPI_Get_processor_name(myname,&len);

if(rank!=0) {


printf("hello from processor %d on %s\n", rank, myname);

}


MPI_Finalize();
return 0;

}
