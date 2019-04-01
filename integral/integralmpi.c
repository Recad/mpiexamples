#include <mpi.h>  
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//using namespace std; 
 //la funcion escogida es  1/x + x^3 entre 
int main(int argc, char *argv[]) { 
	
	
	// Initialize the MPI environment
	MPI_Init(NULL, NULL);
	// Find out rank, size
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	
	if (world_size != 2) {
		fprintf(stderr, "World size must be 2 for %s\n", argv[0]);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}
	
	
	double a, b, w, sum, x_i;
	int i, n;
	
	a = atof(argv[2]);
	b = atof(argv[3]);
	n = atoi(argv[1]);
	
	w = (double) (b-a)/n;
	sum = 0.0;
	
	int n_new = n/2;
	float b_new = ((b-a)/2)+a;
	
	if (world_rank == 0) {
	
	
	
	for (i =0; i<=n_new;i++) {
		
		x_i = a + (i-1)*w;
		sum = sum + (w * ((1/x_i) + (x_i * x_i * x_i)));
		
	}
	
		
    
		MPI_Send(
		/* data         = */ &sum, 
		/* count        = */ 1, 
		/* datatype     = */ MPI_DOUBLE, 
		/* destination  = */ 1, 
		/* tag          = */ 0, 
		/* communicator = */ MPI_COMM_WORLD);
		
		
	} else if (world_rank == 1) {
		 sum=0.0;
		
		MPI_Recv(
		/* data         = */ &sum, 
		/* count        = */ 1, 
		/* datatype     = */ MPI_DOUBLE, 
		/* source       = */ 0, 
		/* tag          = */ 0, 
		/* communicator = */ MPI_COMM_WORLD, 
		/* status       = */ MPI_STATUS_IGNORE);
	
		
		
		for (i =0; i<=n_new;i++) {
		
			x_i = b_new + (i-1)*w;
			sum = sum + (w * ((1/x_i) + (x_i * x_i * x_i)));
		
		}
		printf("el valor aproximado de la integral es %f\n",sum);
	}
		
		MPI_Finalize();
	
	
	
	
	
	
} 
