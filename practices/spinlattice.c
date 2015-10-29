#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 




int main(void) {


double **ArrayVariable;
int NRows,i,Ncols;

ArrayVariable= malloc (NRows * sizeof(double *));

	// if ( ArrayVariable == NULL)

	// {
	//	fprintf(stderr,"OUT OF MEMOORY!\n");

 	//   }

	for (i=0;i<NRows;i++) 

	{
		ArrayVariable[i]== malloc (Ncols * sizeof(double));
	
//	if (ArrayVariable[i]== NULL)
	//	{
	//	fprintf(stderr,"OUT OF MEMOORY!\n");
	//	}

	}

	for (i=0;i<NRows;i++) 
	{
	free(ArrayVariable[i]);
	}
 	free(ArrayVariable);






}
