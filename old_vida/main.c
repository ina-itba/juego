#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "juego.h"
#include "define_general.h"

#define SALIR (printf("Ingreso 'q'. Fin del programa\n"))
#define TAM_CEL 30

extern void* pfree;

// ----- MAIN ----- //
int main(void){

	char mat[ALTO*ANCHO];			// matriz del juego
	char salir = 0;					// flag para salir del programa
	char input;
	char err, tipo = 0;					//la variable tipo indica si el usuario eligio la opcion predeterminada o no
	int tamano = 0;
	int tamanofila = 0;
	unsigned int cont;
	void* pmatriz;
	char* mat2;						//matriz auxiliar para ir cargando los datos de avance de generacion
	char* pall = NULL;

	// ---------- ELECCION MATRIZ INICIAL --------- //

	printf("Quiere ingresar el estado inicial del juego? O prefiere una disposicion predeterminada?\n");
	printf("-Ingrese \"p\" para la opcion predeterminada.\n");
	printf("-Ingrese \"y\" para configurar el estado inicial del juego.\n");

	do {

		err = 0;

		while((input = getchar()) != '\n') {
			
			if(input == 'p' || input == 'P' || ALTO > 26 || ANCHO > 26) {
				
				tipo = PREDETERMINADA;

				tamanofila = ALTO;

				matriz_predeterminada (mat);
				
			}
			
			else if (input == 'y' || input == 'Y') {
				
				input = getchar();	//Se deshace del caracter '\n' que genera problemas en la funcion set
				
				pmatriz = set(&salir, &tamano, &tamanofila);
				
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
		
		if(err == -1) {
			
			printf("Por favor ingrese \"p\" o \"y\" para iniciar el juego");
		
		}
	}
	
	while(err == -1);

	// ---------- AVANCE DE GENERACIONES --------- //	

	if (tipo == PREDETERMINADA) {

		tamano = ANCHO;

		mat2 = calloc (ANCHO, sizeof (char));

		pmatriz = mat;

	}

	mat2 = calloc (tamano, sizeof (char));

	// INTEGRACION DISPLAY ALLEGRO
	// SETUP ALLEGRO
	al_init();
	al_install_keyboard();

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_DISPLAY* disp = al_create_display(tamanofila*TAM_CEL, tamanofila*TAM_CEL);
	ALLEGRO_TIMER * timer = al_create_timer(1.0/30.0);

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	ALLEGRO_EVENT event;

	// dibujar
	al_init_primitives_addon();
	al_start_timer(timer);

	do {

		avance_generaciones (&salir, pmatriz, mat2, tamano, pall);
		al_wait_for_event(queue, &event);

			if(event.type == ALLEGRO_EVENT_TIMER)
			{
				printf("hola\n");
			}
			else if((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)){
				break;
			}

			if(al_is_event_queue_empty(queue))
			{

				display_matriz(pall,tamanofila);
				al_flip_display();

			}

	}

	while (salir != -1);

	SALIR;
	al_destroy_display(disp);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	free (pfree); //En caso de apretar q en el teclado, se libera el espacio en la memoria heap de la matriz original y la auxiliar
	free ((void*) mat2);

	return 0;

}


