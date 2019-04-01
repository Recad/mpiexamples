//#include <mpi.h>  
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//using namespace std; 
  
int main(int argc, char *argv[]) { 
	
	
	
	if (argc ==0 || argc > 2) {
		
		printf("\nArgumentos invalidos\n");
		
		return 0 ; 
			
	}

	
	int puntosCirculo = 0, puntosCuadrado = 0, intervalo = 0; 
	double x_Aleatorio, y_Aleatorio, valorPuntual, pi; 
    int iteraciones = atoi (argv[1]);
	
    
    srand(time(NULL)); 
	
    
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
  
    
    printf("el valor estimado de pi es:  %f \n",pi);
  
    return 0; 
} 
