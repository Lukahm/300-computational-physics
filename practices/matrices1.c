#include<stdio.h>
#include <stdlib.h>
#include<mpi.h>







int main(int argc, char *argv[]){



const int ndim=4;
	int ndim2;


  const int ndim = 4;
  int ndim2;
  int np, my_rank;
  int i, j,k,m,ip;
  MPI_Status status;
  float *mat1, *mat2, *mat3;
  float *x, *y, *z;
  float tr;
  int chunk_size, offset;

 char hostname[MPI_MAX_PROCESSOR_NAME];


// set up matrices 
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Get_processor_name(hostname, &len);


	if (my_rank == 0){

	x=mat1;
	y=mat2;
	z=mat3;

    mat1 = malloc(sizeof(float)*ndim2);  /* The two inputs */
    mat2 = malloc(sizeof(float)*ndim2);
    mat3 = malloc(sizeof(float)*ndim2);  /* The answer */
    /* Some toy values */
   // for( i = 0; i < ndim2; i++ ) {  
    //  mat1[i] = i;
     // mat2[i] = i+1;
    //}
	mat1[0]=0;
	mat2[0]=1;
	
	for(i=0;i<16;i++)
	{
	mat1[i+1]+=mat1[i]+1;
	}
	
	
	for(i=0;i<16;i++)
	{
	mat2[i+1]+=mat2[i]+1;
	}


	}else (
		
	mat1=malloc(sizeof(float)*chunk_size);
	mat2=malloc(sizeof(float)*chunk_size);
	mat3=malloc(sizeof(float)*chunk_size);

	)
		
		
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



//4*4 matrices

//mat1[i]----x


ndim2=ndim*ndim;

chunk_size=ndim2/np;

offset=0;

for(offset=0;offset<=8;offset+4){
	
	for(j=1;j<4;j++){

	MPI_Send(&mat1[offset],chunk_size,MPI_FLOAT,j,1,MPI_COMM_WORLD);
	
	}
}
	


MPI_Recv(&x[0],chunk_size,MPI_FLOAT,0,1,MPI_COMM_WORLD,&status);

	


//Distribute data


	if(my_rank==0) {


		offset=0;
		x=mat1[0];
		y=mat2[0];
		
		for(ip=1;ip<np;ip++){

			for(offset=0;offset<=8;offset+4){
	
				for(j=1;j<4;j++){

	MPI_Send(&mat1[offset],ndim,MPI_FLOAT,ip,1,MPI_COMM_WORLD);
	MPI_Send(&mat2[0],ndim2,MPI_FLOAT,ip,2,MPI_COMM_WORLD);
			}
		}
	
	}
		
	
    	}else{    

 MPI_Recv(&x[0], ndim, MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &status);
 MPI_Recv(&y[0], ndim2, MPI_FLOAT, 0, 2, MPI_COMM_WORLD, &status);
	}

  if( my_rank == 0 ) { 
    printf("Distributed data\n");
    fflush(stdout);
  }

//Do

for( j = 0; j < ndim; j++ ) {
    z[j] = 0;
	for(k=0;k<ndim;k++){
		m=coord(k,j,ndim);
		z[j]+= x[k]*y[m];

	}

  }


  /* Consolidate results */


if(my_rank==0) {
    offset = 0;

      	for(ip=1;ip<np;ip++){
		      offset += chunk_size;


MPI_Recv(&mat3[offset],chunk_size,MPI_FLOAT,ip,3,MPI_COMM_WORLD,&status);
		}          //chunk_size
	}else{ 

		
		MPI_Send(&z,1,MPI_FLOAT,0,3,MPI_COMM_WORLD);
		

	}






if(my_rank==0) {	
	tr=mat3[chunk_size]+mat3[chunk_size];
	
//calculate 4*4
	printf("tr=%f",tr);
}


//Test distribution 

	//

	if(my_rank==0){
		free(mat1);
		free(mat2);
		free(mat3);//FREE(MAT4)
	}


	MPI_Finalize();

	
return 0;



}
