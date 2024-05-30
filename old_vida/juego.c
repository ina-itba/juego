#include "define_general.h"
#include "ingreso_natural.h"
#include "juego.h"
#include <stdio.h>

static int contador (char mat[ALTO][ANCHO], int f, int c);

// CONTADOR ASTERISCOS //
static int contador (char mat[ALTO][ANCHO], int f, int c){ //f y c son las COORDENADAS de la CELULA A ANALIZAR

	// MAT 3X3 RODEANDO PUNTERO //	
	char mat3[3][3]; 				//mat 3 sera una matriz de 3x3 alrededor de la celula a analizar
	int i3=0;						// contador filas mat3
	int j3;	
	int i;
	int j;						// contador columnas mat3. se debe reiniciar en cada for, lo defino abajo.

	for (i=f-1;i<f+2;i++){ 	// contador desde la fila anterior hasta la fila siguiente a puntero
		j3=0;
					
		for (j=c-1;j<c+2;j++){ // contador desde la col anterior hasta la col siguiente a puntero
			//int rowIn = (i < 0) ? 0 : (i >= ALTO ? ALTO - 1 : i);
        	//int colIn = (j < 0) ? 0 : (j >= ANCHO ? ANCHO - 1 : j); 
        	
        	if (i<0 || j<0){
        		mat3[i3][j3] = -1;
        	} else if (i >= ALTO || j >= ANCHO) {
        		mat3[i3][j3] = -1;
        	} else {
        	mat3[i3][j3] = mat[i][j];
        	}
        	j3++;
		}
		i3++;
	}
	
	mat3[1][1]=' ';		// cargo un espacio en el medio de la mat3 por si habia una celula
	
	// CUENTO ASTERISCOS EN LA MAT 3X3 //
	int cast = 0; 		//var cantidad de asteriscos
	
	for (i=0;i<3;i++){ 		
		for (j=0;j<3;j++){ 
			if (mat3[i][j] == '*'){
				cast++;		
			}
		}
	}
	return cast;
}

void avance_generaciones (char* salir, char mat[ALTO][ANCHO]) {

	int cast; // contador asteriscos
	int mat2[ALTO][ANCHO];	// creo una matriz 2 donde ir cargando los datos nuevos para no sobreescribir la matriz que tiene los datos actuales (sobre los cuales trabajo en el mismo loop)
	int gen = ingreso_natural();
	
	if (gen == -1){ 		// escape si ingreso q
		
		*salir = gen;
		return;
	
	}
	
	printf("Avanzando %d generaciones:\n",gen);
	
	for (int g=1; g<=gen;g++){			// este for debe analizar cada casilla y sobreescribirla con la nueva config
	
		for (int i=0;i<ALTO;i++){ 		//por cual fila voy 
			
			cast = 0;
			
			for (int j=0;j<ANCHO;j++){ 	//por cual columna voy
				
				cast = contador(mat,i,j);
				
				switch(mat[i][j]){
					
					case ' ':
						if (cast==3){
							
							mat2[i][j]='*';
						} 
						
						else {
							
							mat2[i][j]=' ';
						}
					break;
					
					case '*':
						if (cast<2){
							
							mat2[i][j]=' ';
						
						} 
						
						else if(cast == 2 || cast == 3){
							
							mat2[i][j]='*';
						
						}
						
						else if(cast>3){
							
							mat2[i][j]=' ';
						
						}
					
					break;
				}
			}
		}
		
	// ----- MAT2 --> MAT ----- //
	// Ahora que ya sali del bucle puedo volver a almacenar en mat los datos obtenidos para volver a modificarlos
	// por el casod de que gen>1	

		for (int y=0;y<ALTO;y++){ 					
			
			for (int x=0;x<ANCHO;x++){ 
				
				mat[y][x] = mat2[y][x];	//copia cada elemento en el mismo lugar pero de la otra matriz (= size)
			
			}
		}
	}	
	
	printf("\n"); //bajo casilla para hacer el nuevo display
	
// ----- DISPLAY NUEVO ----- //		
	for (int i=0;i<ALTO;i++){ //por cual fila voy 
		
		printf("|");
		
		for (int j=0;j<ANCHO;j++){ //por cual columna voy
			
			printf("%c|", mat[i][j]);
		
		}
		
		printf("\n");
	}
	
} 

