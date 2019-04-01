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
	double x_Aleatorio, y_Aleatorio, valorPuntual, pi=0,pinew=0; 
    int iteraciones = atoi (argv[1]);
	
 
	srand(world_rank);
    
   
	  // We are assuming at least 2 processes for this task
	if (world_size != 2) {
		fprintf(stderr, "World size must be 2 for %s\n", argv[0]);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	
	
	if (world_rank == 0) {
		
		 
		for (int i = 0; i < iteraciones; i++) { 
			
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
			
			pi = (double) (4 * puntosCirculo) / puntosCuadrado; 
			
        
		} 
    
		
    
		MPI_Send(
		/* data         = */ &pi, 
		/* count        = */ 1, 
		/* datatype     = */ MPI_DOUBLE, 
		/* destination  = */ 1, 
		/* tag          = */ 0, 
		/* communicator = */ MPI_COMM_WORLD);
		
		printf("se envia pi %f\n", pi);
	} else if (world_rank == 1) {
		 
		
		MPI_Recv(
		/* data         = */ &pi, 
		/* count        = */ 1, 
		/* datatype     = */ MPI_DOUBLE, 
		/* source       = */ 0, 
		/* tag          = */ 0, 
		/* communicator = */ MPI_COMM_WORLD, 
		/* status       = */ MPI_STATUS_IGNORE);
		
		printf("se recibe pi %f\n", pi);
		
		
		
		srand (time (NULL));
		printf("los puntos circulo son %d\n",  puntosCirculo);
		for (int i = 0; i < iteraciones; i++) { 
			
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
			
			pinew = (double) (4 * puntosCirculo) / puntosCuadrado; 
			
        
		} 
		
		
		
		printf("la aporximacion de pi con 2 procesos es %f\n", (pi + pinew)/2);
		
	}
		
		MPI_Finalize();
  
    
} 
