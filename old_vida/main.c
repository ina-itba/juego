#include <stdio.h>
#include "matriz.h"
#include "juego.h"
#include "define_general.h"
#define SALIR (printf("Ingreso 'q'. Fin del programa\n"))

// ----- MAIN ----- //
int main(void){

	char mat[ALTO][ANCHO];			// matriz del juego
	char salir = 0;					// flag para salir del programa
	char input;
	char err;
	unsigned int cont;				

	// ---------- ELECCION MATRIZ INICIAL --------- //

	printf("Quiere ingresar el estado inicial del juego? O prefiere una disposicion predeterminada?\n");
	printf("-Ingrese \"p\" para la opcion predeterminada.\n");
	printf("-Ingrese \"y\" para configurar el estado inicial del juego.\n");

	do {
		err = 0;
		while((input = getchar()) != '\n'){
			
			if(input == 'p' || input == 'P' || ALTO>26 || ANCHO>26){
				
				matriz_predeterminada (mat);
				
			}
			
			else if(input == 'y' || input == 'Y'){
				
				input = getchar();	//Se deshace del caracter '\n' que genera problemas en la funcion set
				
				set(mat, &salir);
				
				if(salir == -1) {
					
					SALIR;
					
					return 0;
				}
				
				break;				//Al deshacerse del caracter '\n' se debe salir del loop con un "break"
			}
			
			else {
				
				err = -1;
			}
			
			cont++;
		}
		
		if(err == -1){
			
			printf("Por favor ingrese \"p\" o \"y\" para iniciar el juego");
		
		}
	}
	
	while(err == -1);

	// ---------- AVANCE DE GENERACIONES --------- //	

	do {

		avance_generaciones (&salir, mat);
	
	}
	
	while (salir != -1);
	
	SALIR;

	return 0;

}


