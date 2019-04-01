#include <mpi.h>  
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//using namespace std; 
  
int main(int argc, char *argv[]) { 
	
	
	
	 
	
	// Initialize the MPI environment
	MPI_Init(NULL, NULL);
	// Find out rank, size
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	
	
	int puntosCirculo = 0, puntosCuadrado = 0, intervalo = 0; 
	double x_Aleatorio, y_Aleatorio, valorPuntual, pi=0,pinew,pisum=0; 
    int iteraciones = atoi (argv[1]);
	double *globalpi=NULL;
 
	
    
   
	  // We are assuming at least 2 processes for this task
	if (world_size < 2) {
		fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	
		srand(world_rank+time(NULL));
		
		for (int i = 0; i < iteraciones/world_size; i++) { 
			
			// generar los valores de x y y aleatoriamente
			x_Aleatorio = (double)(rand() % iteraciones+1)/iteraciones; 
			y_Aleatorio = (double)(rand() % iteraciones+1)/iteraciones; 
			
			//printf("valor x :%f \n",x_Aleatorio );
			//printf("valor y :%f\n",y_Aleatorio);
			
			// Distance between (x, y) from the origin 
			valorPuntual = x_Aleatorio * x_Aleatorio + y_Aleatorio * y_Aleatorio; 
			
			
			if (valorPuntual  <= 1) {
				
				puntosCirculo++; 
	  
			}
			puntosCuadrado++;
			
			pi = (double) (puntosCirculo) / puntosCuadrado; 
			
        
		} 
		MPI_Send(
		/* data         = */ &pi, 
		/* count        = */ 1, 
		/* datatype     = */ MPI_DOUBLE, 
		/* destination  = */ 0, 
		/* tag          = */ 0, 
		/* communicator = */ MPI_COMM_WORLD);
		
			//MPI_Wait(&request, &status);
			
		
	
	if (world_rank == 0) {
		
		
		globalpi = malloc(world_size * sizeof(double));
		
	} 
	
	
		MPI_Gather(
				/* data         = */ &pi, 
				/* count        = */ 1, 
				/* datatype     = */ MPI_DOUBLE,
				/* recv_data	= */ globalpi,
				/* recv_count   = */ 1, 
				/* recv_datatype= */ MPI_DOUBLE, 
				/* root         = */ 0,
				/* mpi_comm		= */ MPI_COMM_WORLD/*&request*/);
	
	
	if (world_rank == 0) {
		
		
		for (int i=0; i<world_size; i++)
            pisum = pisum + globalpi[i];
        
		
		printf("el valor aproximado de pi con %d procesos es: %f\n", world_size,(double) 4*(pisum/world_size));
		
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

