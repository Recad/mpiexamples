//#include <mpi.h>  
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//using namespace std; 
 //la funcion escogida es  1/x + x^3 entre 
int main(int argc, char *argv[]) { 
	
	double a, b, w, sum, x_i;
	int i, n;
	
	a = atof(argv[2]);
	b = atof(argv[3]);
	n = atoi(argv[1]);
	
	w = (double) (b-a)/n;
	sum = 0.0;
	
	for (i =0; i<=n;i++) {
		
		x_i = a + (i-1)*w;
		sum = sum + (w * ((1/x_i) + (x_i * x_i * x_i)));
		
	}
	
	printf("el valor aproximado de la integral es %f\n",sum);
    return 0; 
} 


