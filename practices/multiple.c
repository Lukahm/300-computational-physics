/* mpi_add2.c */

/* Initialises two matrices and then adds them. Includes partitioning of data.*/


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


int coord(int i, int j, int nj){

return j+i*nj;

}

int main (int argc, char *argv[])
{
  const int ndim = 4;
  int ndim2;
  int np, my_rank;
  int i, j,k,m,ip;
  MPI_Status status;
  float *mat1, *mat2, *mat3;
  float *x, *y, *z;
  float tr;
  int  offset;
  

  /* Usual MPI startup stuff */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  ndim2 = ndim*ndim;

  /* Set up the matrices */
  if( my_rank == 0 ) {
    mat1 = malloc(sizeof(float)*ndim2);  /* The two inputs */
    mat2 = malloc(sizeof(float)*ndim2);
    mat3 = malloc(sizeof(float)*ndim2);  /* The answer */
    /* Some toy values */
    for( i = 0; i < ndim2; i++ ) {  
      mat1[i] = i;
      mat2[i] = i+1;
    }
  } else {
    x = malloc(sizeof(float)*ndim);
    y = malloc(sizeof(float)*ndim2);
    z = malloc(sizeof(float)*ndim);
  }


  /* Print out input */
  if( my_rank == 0 ) {
    printf("Input Data\n");
    printf("A = ");
    for( i = 0; i < ndim2; i++ ) {  
      printf("%f ", mat1[i]);
      if( (i+1)%ndim == 0) printf("\n    ");
    }
    printf("\nB = ");
    for( i = 0; i < ndim2; i++ ) {  
      printf("%f ", mat2[i]);
      if( (i+1)%ndim == 0 ) printf("\n    ");
    }
    printf("\n");
    fflush(stdout);
  }
  
  
  /* Distribute data */
  if( my_rank == 0 ) {
    offset = 0;
    for( ip = 1; ip < np; ip++ ) {
      offset += ndim;
      MPI_Send(&mat1[offset], ndim, MPI_FLOAT, ip, 1, MPI_COMM_WORLD);
      MPI_Send(&mat2[0], ndim2, MPI_FLOAT, ip, 2, MPI_COMM_WORLD);
    }
    x = mat1;
    y = mat2;
    z = mat3;
  } else {
    MPI_Recv(&x[0], ndim, MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&y[0], ndim2, MPI_FLOAT, 0, 2, MPI_COMM_WORLD, &status);
    }

  if( my_rank == 0 ) { 
    printf("Distributed data\n");
    fflush(stdout);
  }
    
  /* Do work */
  for( j = 0; j < ndim; j++ ) {
    z[j] = 0;
	for(k=0;k<ndim;k++){
		m=coord(k,j,ndim);
		z[j]+= x[k]*y[m];

	}

  }

printf("\n%f\n",*z);

  /* Consolidate results */
  if( my_rank == 0 ) {
    offset = 0;
    for( ip = 1; ip < np; ip++ ) {  
      offset += ndim;
      MPI_Recv(&mat3[offset], ndim, MPI_FLOAT, ip, 3, MPI_COMM_WORLD, &status);
    }
  } else {
    MPI_Send(&z[0], ndim, MPI_FLOAT, 0, 3, MPI_COMM_WORLD);
  }

  fflush(stdout);
  if( my_rank == 0 ) {
    printf("Output Data\n");
    printf("C = ");
    for( i = 0; i < ndim2; i++ ) {  
      printf("%f ", mat3[i]);
      if( (i+1)%ndim == 0) printf("\n    ");
    }
    printf("\n");
  }
  
  /* Take trace */
  if( my_rank == 0 ) {
    offset = 0;
    tr = 0;
    for( i = 0; i < ndim; i++ ) {
      tr += mat3[offset];
      offset += ndim + 1;
    }
    printf("Tr C = %f\n", tr);
  }

  /* Clean up */
  if(  my_rank == 0 ) {
    free(mat1);
    free(mat2);
    free(mat3);
  } else {
    free(x);
    free(y);
    free(z);
  }
  
  MPI_Finalize();
  return 0;
  }
