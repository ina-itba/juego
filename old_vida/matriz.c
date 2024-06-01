#include "matriz.h"
#include "define_general.h"
#include <stdio.h>
#include <stdlib.h>
#include "ingreso_natural.h"

static unsigned char ingresoCelula(void);			//Funcion para ingresar por teclado el estado de una celula
static void* tamano (int size);
//static void impresionMatriz (char* pmatriz);

void * pfree;						//puntero para liberar espacio en el heap (global multiarchivo)

void matriz_predeterminada (char mat[ALTO][ANCHO]) {

	int a, b, i, j;

// defino mat opc A
	printf("\nOpción A: \n");

	for (a = 0;a < ALTO;a++){ 		// por cual fila voy
		
		for (b = 0;b < ANCHO;b++){ 	// por cual columna voy
			
			mat[a][b]= ' '; 		// defino espacios en todo el array
			
			// defino configuracion de asteriscos iniciales
			
			if (a==b && (a<(int)(ALTO/2)+2) && (a>(int)(ALTO/2)-2)) {// condiciones rndms para dibujo inicial
				mat[a][b]= '*';
			}
			
			mat[(int)(ALTO/2)][(int)(ANCHO/2)+1] = '*';
			mat[((int)(ALTO/2)-2)][(int)(ANCHO/2)] = '*';
			mat[(int)(ALTO/2)][(int)(ANCHO/2)+3] = '*';
			mat[((int)(ALTO/2)-4)][(int)(ANCHO/2)] = '*'; //esta config muere a los 20 aprox. queda al borde cuadrada.
			
		}
		
	}
	// ----- DISPLAY A ----- //
	for (i = 0;i < ALTO;i++){ //por cual fila voy
		
		printf("|");
		
		for (j = 0;j < ANCHO;j++){ //por cual columna voy
			
			printf("%c|", mat[i][j]);
		
		}
		
		printf("\n");
		
	}
		
	printf("\n"); //bajo renglon para facha

}

static unsigned char ingresoCelula(void)
{
	unsigned char cel = 0;
	char err;			//Flag para determinar si hubo un error al ingresar el estado de la celula
	unsigned char c;
	unsigned int cont;	//Determina la cantidad de caracteres ingresados por teclado
	char automatico; 	//Flag para determinar si el usuario quiere llenar el resto de la matriz de manera automatica
	
	do {

		err = 0;
		cont = 0;
		automatico = 0;

		while((c = getchar()) != '\n') {				//Lee los caracteres ingresados hasta encontrar un "Enter"

			if(cont == 0 && c == 'q' && automatico == 0) {	//Si el primer caracter ingresado es 'q', se termina el programa

				return 'q';

			}

			else if(cont == 0 && (c == 'a' || c == 'A')) {	//Si el primer caracter es 'a', significa que el usuario quiere autocompletar

				automatico = 1;						//No aumenta el contador para no activar el flag de error

			}

			else {

				if(c == 'v' || c == 'V') {	//Ingreso de celula viva

					cel = '*';

				}

				else if (c == 'm' || c == 'M') {		//Ingreso de celula muerta

					cel = ' ';

				}
				else {								//Para cualquier otro caracter indica error

					err = -1;

				}

				cont++;

			}

		}

		if(cont > 1 || (cont == 0 && automatico == 1) || (cont == 0 && c == '\n')) { //Si se ingreso mas de un caracter,se ingreso una 'a' y nada mas indica error o solo un enter

				err = -1;

		}

		if(err == -1) {

			printf("Error, intente ingresar el estado de la celula nuevamente: ") ;

		}

	}
	while(err == -1);						//Repite el loop hasta que no haya errores

	if(automatico == 1 && cel == '*') {

		return 'v';	

	}

	else if(automatico == 1 && cel == ' ') {

		return 'm';

	}

	else {

		return cel;

	}

}

void* set(char* salir, int* tamanomatriz) {
	
	int i,j,k,p;
	unsigned char grillaFila;			//Posicion de la columna en la grilla
	unsigned char grillaColumna;		//Posicion de la fila en la grilla
	unsigned char ingresoColumna;
	unsigned char ingresoFila = 'A';
	unsigned char celula = 0;				//Guarda el estado de la celula
	unsigned char automatico = 0;			//Flag para que se autocomplete el resto de la matriz
	int tamanoMatrizfila = 0;			//tamaño definido para las filas y columnas de la matriz en la ejecucion
	char * pmatrizdefinida;				//puntero a matriz en heap
	void * pmatrizfinal;

	printf("Ingrese el tamaño de la matriz cuadrada: \n");

	tamanoMatrizfila = ingreso_natural();

	pmatrizdefinida = tamano (tamanoMatrizfila);

	pfree = pmatrizdefinida;
	pmatrizfinal = pmatrizdefinida;

	*tamanomatriz = tamanoMatrizfila;
	
	for(i = 0; i < (tamanoMatrizfila * tamanoMatrizfila); i += tamanoMatrizfila) {			//Seteo la matriz a espacios

		for (j = 0;j < tamanoMatrizfila; j++) {

			pmatrizdefinida [i+j] = ' ';

		}
	}

	printf("/-------------------------------------------------------------/\n");
	printf("La primer celula a setear sera la de la esquina superior izquierda, luego seguira hacia la derecha hasta completar la grilla.\n");
	printf("-Ingrese \"m\" para setear una celula muerta.\n");
	printf("-Ingrese \"v\" para setear una celula viva.\n");
	printf("-Ingrese \"av\" para autocompletar el resto de la matriz con celulas vivas.\n");
	printf("-Ingrese \"am\" para autocompletar el resto de la matriz con celulas muertas.\n");
	
	for(i = 0; i < (tamanoMatrizfila*tamanoMatrizfila); i += tamanoMatrizfila) {		//Ingreso celulas vivas o muertas a la matriz

		ingresoColumna = 'a';

		for(j = 0; j < tamanoMatrizfila; j++) {

			printf("%c%c:\n", ingresoFila, ingresoColumna);	//Coordenada en la que se encuentra la celula

			ingresoColumna++;
			
			if(automatico  == 0) {				//Si no eligio autocompletar, el estado de la celula sera el ingresado

				celula = ingresoCelula();

				if(celula == 'q') {

					*salir = -1;

					return salir;
					
				}
				
				else if(celula == 'v') {
					
					automatico = 1;
					celula = '*';
					pmatrizdefinida[i+j] = celula;

				}
				
				else if(celula == 'm'){
					
					automatico = 1;
					celula = ' ';
					pmatrizdefinida[i+j] = celula;
				}
				
				else {
					
					pmatrizdefinida[i+j] = celula;
				}
				
			}
			
			else {											//Si eligio autocompletar, no lee mas el teclado y rellena la matriz de manera automatica
			
				pmatrizdefinida[i+j] = celula;

			}

			/*------Codigo para imprimir en pantalla el estado de la matriz------*/

			grillaFila = 'A';								
			grillaColumna = 'a';

			for(k = 0; k < (tamanoMatrizfila*tamanoMatrizfila) + 1; k += tamanoMatrizfila) {	//Imprimo el estado de la matriz en tiempo real

				for(p = 0; p < tamanoMatrizfila + 1; p++) {

					if(k == 0 && p == 0) {	//El primer lugar es un espacio vacio

						putchar(' ');

					}

					else if(k == 0 && p >= 1) {	//En la primera fila se encuentran las coordenadas de las columnas

						printf(" %c ",grillaColumna);
						grillaColumna++;

					}

					else if (p == 0) {			//En la primera columna se encuentran las coordenadas de las filas

						putchar(grillaFila); 
						grillaFila++;

					}

					else {

						printf("|%c|", pmatrizdefinida[k + p - tamanoMatrizfila - 1]);

					}
				}

				printf("\n");

			}

		}

		ingresoFila++;
	}

	return pmatrizfinal;
}

static void* tamano (int size) {

	void* pmatriz;

	pmatriz = calloc ((size*size), sizeof(char));

	return pmatriz;

}
