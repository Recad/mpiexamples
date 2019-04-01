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
	double *globaldata=NULL;
    double localdata;
	
	if (world_size < 2) {
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
	
	
	/*
	
	
	*/
		
    
	
		
		
	if (world_rank == 0) {
		
		globaldata = malloc(world_size * sizeof(double) );
        for (int i=0; i<world_size; i++)
            globaldata[i] = a+(i*w);

        
     } 
		MPI_Scatter(
			globaldata,
			1,
			MPI_DOUBLE,
			&localdata,
			1,
			MPI_DOUBLE,
			0,
			MPI_COMM_WORLD);
		
		for (i =0; i<=n;i++) {
		
			x_i = localdata + (i-1)*w;
			sum = sum + (w* ((1/x_i) + (x_i * x_i * x_i)));
		
		}
		
		
		MPI_Gather(
				/* data         = */ &sum, 
				/* count        = */ 1, 
				/* datatype     = */ MPI_DOUBLE,
				/* recv_data	= */ globaldata,
				/* recv_count   = */ 1, 
				/* recv_datatype= */ MPI_DOUBLE, 
				/* root         = */ 0,
				/* mpi_comm		= */ MPI_COMM_WORLD/*&request*/);
	
	
	if (world_rank == 0) {
		
		double megasum=0.0;
		for (int i=0; i<world_size; i++)
            megasum = megasum + globaldata[i];
        
		printf("el valor aproximado de la integral es %f\n",megasum/world_size);
		/*
		MPI_Scatter(
			globalpi,
			1,
			MPI_DOUBLE,
			&pinew,
			1,
			MPI_DOUBLE,
			world_rank,
			MPI_COMM_WORLD);*/
	}
		
		
		
		MPI_Finalize();
	
	
	
	
	
	
} 
