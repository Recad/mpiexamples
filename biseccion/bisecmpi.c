#include <mpi.h>  
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
#define RAIZ(x) ((x)+2) // Definimos la funcion de la que se busca la raiz
 
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
	
	
	float superior, inferior, valor_intermedio, valoranterior, erroraproximado;
	int iteraciones;
	superior = atoi(argv[1]);
	inferior = atoi(argv[2]);

 
	iteraciones = 0;
	valoranterior = 0.0;
	erroraproximado = 0;
	
 
	do{
		iteraciones++;
		valor_intermedio = (superior + inferior) / 2;
		if(iteraciones >= 2) {
			erroraproximado = ((valor_intermedio - valoranterior) / valor_intermedio) * 100; // Calculamos el error aproximado a partir de la segunda iteración
		}
		erroraproximado = fabs(erroraproximado); // Calculamos el valor absoluto del número
		
		valoranterior = valor_intermedio;
		if(RAIZ(valor_intermedio) > 0) {
			superior = valor_intermedio;
		} else{
			inferior = valor_intermedio;
		}
 
	} while(erroraproximado > 0.5 || (erroraproximado == 0.0 && iteraciones == 1));
 
	printf("\nLa raiz es : %f\n", valor_intermedio);
 
	return 0;
}
