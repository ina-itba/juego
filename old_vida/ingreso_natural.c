#include "ingreso_natural.h"
#include <stdio.h>

static int decimal(int);

int ingreso_natural (void) { 		// la funcion tiene que indicar si se ingreso un dato correcto (numero)

	char c;
	char err; 					// flag para saber si hubo error (no esta entre los ascis numericos)
	unsigned int gen; 			// variable que devolvera: la cantidad de generaciones
	
	do {
		
		err = 0; 			// reiniciamos flag error
		gen = 0;			// reinicio num gen, el calculado antes se descarta (esto si es la segunda vez del do)
		c = 0;				// reiniciamos para pedir entrada de nuevo
		
		while ((c = getchar()) != '\n') {	// evalua valores de entrada hasta el ultimo en la entrada, el
										// enter (que envio el user)						
			if (c == 'q') {

				return -1;

			}
						
			c = decimal(c);		// convierto el caracter a decimal. ahora c tiene un 
								// valor del 0 al 9. (salvo comas o neg)
			if (c < 0 || c > 9) {	// DETERMINO SI HUBO ERRORES: no era un numero ni char 'q'

				err = -1; 					

			} 			
						
			gen = gen * 10 + c;  // hago numero gen, multiplico por 10 lo q tenia y le sumo el nuevo digito.

		}
		
		if (err == -1) {

			printf("El numero ingresado no es valido, ingrese otro: ");

		}
			
	}

	while (err == -1);		// si estamos obteniendo algun error, repetimos el proceso de getchar

	return gen; 		// devuelve el numero de generaciones en int		

}

// CONVERSOR ASCII A DECIMAL //
static int decimal (int x) {			// si es un numero del 0 al 9, restandole 48, por ASCII '0', tendra su valor real.

	return x -= '0';

}


