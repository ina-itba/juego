#include "define_general.h"
#include "ingreso_natural.h"
#include "juego.h"
#include <stdio.h>
#include <stdlib.h>

static int contador (void* pmatriz, int f, int c, int tamaño);

// CONTADOR ASTERISCOS //
static int contador (void* pmatriz, int f, int c, int tamaño){ //f y c son las COORDENADAS de la CELULA A ANALIZAR

	// MAT 3X3 RODEANDO PUNTERO //	
	char mat3[3][3]; 				//mat 3 sera una matriz de 3x3 alrededor de la celula a analizar
	int i3 = 0;						// contador filas mat3
	int j3;	
	int i;
	int j;						// contador columnas mat3. se debe reiniciar en cada for, lo defino abajo.
	char * p;

	p = pmatriz;

	for (i = f-1;i < f+2;i += tamaño) { 	// contador desde la fila anterior hasta la fila siguiente a puntero

		j3 = 0;
					
		for (j = c-1;j < c+2;j++){ // contador desde la col anterior hasta la col siguiente a puntero
			//int rowIn = (i < 0) ? 0 : (i >= ALTO ? ALTO - 1 : i);
        	//int colIn = (j < 0) ? 0 : (j >= ANCHO ? ANCHO - 1 : j); 
        	
        	if (i < 0 || j < 0){

        		mat3[i3][j3] = -1;

        	}

        	else if (i >= ALTO || j >= ANCHO) {

        		mat3[i3][j3] = -1;

        	}
        	else {

        		mat3[i3][j3] = p[i+j];
        	}

        	j3++;

		}

		i3++;

	}
	
	mat3[1][1]=' ';		// cargo un espacio en el medio de la mat3 por si habia una celula
	
	// CUENTO ASTERISCOS EN LA MAT 3X3 //
	int cast = 0; 		//var cantidad de asteriscos
	
	for (i = 0;i < 3;i++){
		for (j = 0;j < 3;j++){

			if (mat3[i][j] == '*') {

				cast++;		

			}
		}
	}

	return cast;
}

void avance_generaciones (char* salir, void* pmatriz, int tamaño) {

	int cast; // contador asteriscos
	char* mat2;	// creo una matriz 2 donde ir cargando los datos nuevos para no sobreescribir la matriz que tiene los datos actuales (sobre los cuales trabajo en el mismo loop)
	int gen;
	int g, i, j, x, y;
	char *p;

	mat2 = calloc (tamaño, sizeof (char));

	p = pmatriz;
	
	printf("Ingrese cantidad de generaciones a avanzar:\n");

	gen = ingreso_natural();

	if (gen == -1){ 		// escape si ingreso q
		
		*salir = gen;
		return;
	
	}
	
	printf("Avanzando %d generaciones:\n",gen);
	
	for (g = 1; g <= gen;g++){			// este for debe analizar cada casilla y sobreescribirla con la nueva config
	
		for (i = 0;i < (tamaño*tamaño);i += tamaño){ 		//por cual fila voy
			
			cast = 0;
			
			for (j = 0;j < tamaño;j++) { 	//por cual columna voy
				
				cast = contador(pmatriz,i,j, tamaño);
				
				switch(p[i+j]){
					
					case ' ':

						if (cast==3){
							
							mat2[i+j] = '*';
						} 
						
						else {
							
							mat2[i+j] = ' ';
						}
					
						break;

					case '*':

						if (cast < 2) {
							
							mat2[i+j]=' ';
						
						} 
						
						else if (cast == 2 || cast == 3) {
							
							mat2[i+j] = '*';
						
						}
						
						else if(cast > 3) {
							
							mat2[i+j]=' ';
						
						}
					
					break;

				}

			}

		}
		
	// ----- MAT2 --> MAT ----- //
	// Ahora que ya sali del bucle puedo volver a almacenar en mat los datos obtenidos para volver a modificarlos
	// por el casod de que gen>1	

		for (y = 0;y < (tamaño*tamaño);y += tamaño){
			
			for (x = 0;x < tamaño;x++){
				
				p[y+x] = mat2[y+x];	//copia cada elemento en el mismo lugar pero de la otra matriz (= size)
			
			}
		}
	}	
	
	printf("\n"); //bajo casilla para hacer el nuevo display
	
// ----- DISPLAY NUEVO ----- //		
	for (i = 0;i < (tamaño*tamaño);i += tamaño){ //por cual fila voy
		
		printf("|");
		
		for (j = 0;j < tamaño;j++){ //por cual columna voy
			
			printf("%c|", p[i+j]);
		
		}
		
		printf("\n");
	}
	
} 

