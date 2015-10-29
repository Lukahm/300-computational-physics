#include<stdio.h>
#include <stdlib.h>
#include<mpi.h>

const int ndim=4;
	int ndim2;



float *mat1,*mat2,*mat3;
float x,y,z,tr;

MPI_Status status;
 int np, my_rank, len,ip;
 char hostname[MPI_MAX_PROCESSOR_NAME];

int main(int argc, char *argv[]){

// set up matrices 
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Get_processor_name(hostname, &len);

//4*4 matrices

mat1[i]----x


ndim2=ndim*ndim;

chunk_size=ndim2/np;

offset=;


MPI_Send(&mat1[offset],chunk_size,MPI_FLOAT,ip,1,MPI_COMM_WORLD);

MPI_Recv(&x[0],chunk_size,MPI_FLOAT,ip,1,MPI_COMM_WORLD,&status);
	})

x=mat1;




	if (my_rank == 0){

	mat1=malloc(sizeof(float)*4);
	mat2=malloc(sizeof(float)*4);
	mat3=malloc(sizeof(float)*4);




	mat1[0]=0;
	mat1[1]=1;
	mat1[2]=2;
	mat1[3]=3;



	mat2[0]=1;
	mat2[1]=2;
	mat2[2]=3;
	mat2[3]=4;
	}




//Distribute data


	if(my_rank==0) {
		x=mat1[0];
		y=mat2[0];
		
		for(ip=1;ip<np;ip++){
		MPI_Send(&mat1[ip],1,MPI_FLOAT,ip,1,MPI_COMM_WORLD);
		MPI_Send(&mat2[ip],1,MPI_FLOAT,ip,2,MPI_COMM_WORLD);
		}
	
    	}else{ MPI_Recv(&x,1,MPI_FLOAT,0,1,MPI_COMM_WORLD,&status);
	       MPI_Recv(&y,1,MPI_FLOAT,0,2,MPI_COMM_WORLD,&status);
	}

	printf("process %d has %f and %f\n",my_rank,x,y);

//Add A to B

	z=x+y;


	if(my_rank==0) {
        mat3[0]=z;

       		for(ip=1;ip<np;ip++){
		
	MPI_Recv(&mat3[ip],1,MPI_FLOAT,ip,3,MPI_COMM_WORLD,&status);
		}
	}else{ 

		
		MPI_Send(&z,1,MPI_FLOAT,0,3,MPI_COMM_WORLD);
		

	}

if(my_rank==0) {	
	tr=mat3[0]+mat3[3];

	printf("tr=%f",tr);
}


//Test distribution 

	//

	if(my_rank==0){
		free(mat1);
		free(mat2);
		free(mat3);
	}


	MPI_Finalize();

	
return 0;



}
