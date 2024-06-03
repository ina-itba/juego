#include "define_general.h"
#include "ingreso_natural.h"
#include "juego.h"
#include <stdio.h>
#include <stdlib.h>
//allegro

#define TAM_CEL 30

static int contador (void* pmatriz, int f, int c, int tamano);

// CONTADOR ASTERISCOS //
static int contador (void* pmatriz, int f, int c, int tamano){ //f y c son las COORDENADAS de la CELULA A ANALIZAR

	// MAT 3X3 RODEANDO PUNTERO //	
	char mat3[3][3]; 				//mat 3 sera una matriz de 3x3 alrededor de la celula a analizar
	int i3 = 0;						// contador filas mat3
	int j3;	
	int i;
	int j;						// contador columnas mat3. se debe reiniciar en cada for, lo defino abajo.
	char * p;

	p = pmatriz;

	for (i = f-1;i < f+2;i += tamano) { 	// contador desde la fila anterior hasta la fila siguiente a puntero

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

void avance_generaciones (char* salir, void* pmatriz, char * mat2, int size, char * pall) {


	int cast; // contador asteriscos
	int gen;
	int g, i, j, x, y;
	char *p = pmatriz;

	
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

		for (y = 0;y < (size*size);y += size){
			
			for (x = 0;x < size;x++){
				
				p[y+x] = mat2[y+x];	//copia cada elemento en el mismo lugar pero de la otra matriz (= size)
			
			}
		}
	}	
	pall = p;

}


void display_matriz(char* p,int tamanofila){

	int n_cuad = 0;
	int size = tamanofila*tamanofila;

	for(int i = 0; i<size; i+=tamanofila){
			for(int j=0; j<tamanofila; j++){
				if( p[i+j] == '*'){
					// dibujamos una celula
					al_draw_filled_rectangle(j*TAM_CEL,n_cuad*TAM_CEL,j*TAM_CEL+TAM_CEL,n_cuad*TAM_CEL+TAM_CEL,al_map_rgb_f(255,0,0));
				}
			}
			n_cuad++;
		}

	// hacemos las lineas separadoras de celulas
	for(int i = 0; i < size; i++){
			al_draw_line(0,i*TAM_CEL,tamanofila*TAM_CEL,i*TAM_CEL,al_map_rgb_f(128,128,128), 1);
			al_draw_line(i*TAM_CEL,0,i*TAM_CEL,tamanofila*TAM_CEL,al_map_rgb_f(128,128,128), 1);
		}

}

