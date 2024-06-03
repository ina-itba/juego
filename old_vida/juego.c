#include "define_general.h"
#include "ingreso_natural.h"
#include "juego.h"
#include <stdio.h>
#include <stdlib.h>
//allegro

#define TAM_CEL 30

static int contador (char* pmatriz, int f, int c, int tamano);

// CONTADOR ASTERISCOS //
static int contador (char* pmatriz, int f, int c, int tamano){ //f y c son las COORDENADAS de la CELULA A ANALIZAR

	// MAT 3X3 RODEANDO PUNTERO //	
	char mat3[3][3]; 				//mat 3 sera una matriz de 3x3 alrededor de la celula a analizar
	int i3 = 0;						// contador filas mat3
	int j3;	
	int i;
	int j;						// contador columnas mat3. se debe reiniciar en cada for, lo defino abajo.

	for (i = f-1;i < f+2;i++) { 	// contador desde la fila anterior hasta la fila siguiente a puntero

		j3 = 0;
					
		for (j = c-1;j < c+2;j++){ // contador desde la col anterior hasta la col siguiente a puntero
			//int rowIn = (i < 0) ? 0 : (i >= ALTO ? ALTO - 1 : i);
        	//int colIn = (j < 0) ? 0 : (j >= ANCHO ? ANCHO - 1 : j); 
        	
        	if (i < 0 || j < 0){

        		mat3[i3][j3] = -1;

        	}

        	else if (i >= tamano*tamano || j >= tamano) {

        		mat3[i3][j3] = -1;

        	}
        	else {

        		mat3[i3][j3] = pmatriz[i*tamano+j];
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

void avance_generaciones (char* salir, char * pmatriz, char * mat2, int size) {


	int cast; // contador asteriscos
	int gen;
	int g, i, j, x, y;

	
	printf("Ingrese cantidad de generaciones a avanzar:\n");

	gen = ingreso_natural();

	if (gen == -1) { 		// escape si ingreso q
		
		*salir = gen;
		return;
	
	}
	
	printf("Avanzando %d generaciones:\n",gen);
	
	for (g = 1; g <= gen;g++) {			// este for debe analizar cada casilla y sobreescribirla con la nueva config
	
		for (i = 0;i < (size*size);i += size){ 		//por cual fila voy
			
			cast = 0;
			
			for (j = 0;j < size;j++) { 	//por cual columna voy
				
				cast = contador(pmatriz,i,j, size);
				
				switch(pmatriz[i+j]){
					
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

		for (y = 0;y < (size*size);y += size){
			
			for (x = 0;x < size;x++){
				
				pmatriz[y+x] = mat2[y+x];	//copia cada elemento en el mismo lugar pero de la otra matriz (= size)
			
			}
		}
	}	

}

