/*
 * main.c
 *
 *  Created on: May 29, 2024
 *      Author: dante
 */


#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

//void setupAllegro(int f, int c, ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* disp);
void display_matriz(char* p,int f, int c);
/*
void setupAllegro(int f, int c, ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* disp){

	al_init();
	al_install_keyboard();

	// creamos timer para monitorear eventos basados en el tiempo, como
	// puede ser refrescar el display. Creamos cola de eventos y un display.
	timer = al_create_timer(1.0 / 30.0);
	queue = al_create_event_queue();
	disp = al_create_display(320, 160);
	// ALLEGRO_FONT* font = al_create_builtin_font();

	// "avisamos" a Allegro que estamos interesados en monitorear eventos
	// del teclado, el display, y el paso del tiempo.
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	//must_init(al_init_primitives_addon(), "primitives");
	al_init_primitives_addon();


}*/

int main(void){
/*
	al_init();
		al_install_keyboard();

		// creamos timer para monitorear eventos basados en el tiempo, como
		// puede ser refrescar el display. Creamos cola de eventos y un display.
		ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
		ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
		ALLEGRO_DISPLAY* disp = al_create_display(320, 160);
		// ALLEGRO_FONT* font = al_create_builtin_font();

		// "avisamos" a Allegro que estamos interesados en monitorear eventos
		// del teclado, el display, y el paso del tiempo.
		al_register_event_source(queue, al_get_keyboard_event_source());
		al_register_event_source(queue, al_get_display_event_source(disp));
		al_register_event_source(queue, al_get_timer_event_source(timer));

		//must_init(al_init_primitives_addon(), "primitives");

		al_init_primitives_addon();*/

	int f,c;
	/*
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_DISPLAY* disp;
	// flag
	bool redraw = true;
	// creamos la variable tipo "union" que
	ALLEGRO_EVENT event;
	*/

	//setupAllegro(f,c,timer,queue,disp);

	al_init();
	al_install_keyboard();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_DISPLAY* disp = al_create_display(320, 160);
	ALLEGRO_FONT* font = al_create_builtin_font();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool redraw = true;
	ALLEGRO_EVENT event;

	// dibujar
	al_init_primitives_addon();

	//iniciamos contador de tiempo (clock)
	al_start_timer(timer);

	while(1){
		al_wait_for_event(queue, &event);

		if(event.type == ALLEGRO_EVENT_TIMER){
			redraw = true;
		}else if((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)){
            break;
		}

		if(redraw && al_is_event_queue_empty(queue))
		{
			//al_clear_to_color(al_map_rgb(0, 0, 0));
			//al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");

			char p[32*32];	//arr de ejemplo, lo manejamos como gran arr

			int f=32;
			int c=32;
			for(int i = 0; i<(f*c); i+=c){
				for(int j=0; j<32; j++){
					if((j%2) != 0){
						*(p+i+j) = ' ';
					}else {
						*(p+i+j) = '*';
					}
				}
			}

			display_matriz(p,32,32);

			al_flip_display();

			redraw = false;
		}



	}

}

void display_matriz(char* p,int f, int c){

	int tam_cel = 10;

	for(int i = 0; i<(f*c); i+=c){
		for(int j=0; j<32; j++){
			//if(p[i][j] == '*'){		//funciona on tipo de dato matriz, tenemos q hacer funcionar con punteros
			if( *(p+i+j) == '*'){
				// dibujamos una celula
				al_draw_filled_rectangle(i*tam_cel,j*tam_cel,i*tam_cel+tam_cel,j*tam_cel+tam_cel,al_map_rgb_f(255,0,0));
			}

		}

	}

	// hacemos las lineas separadoras de celulas
	for(int i = 0; i < (f*c)-1; i++){
			al_draw_line(0,i*tam_cel,c*tam_cel,i*tam_cel,al_map_rgb_f(128,128,128), 1);
			al_draw_line(i*tam_cel,0,i*tam_cel,c*tam_cel,al_map_rgb_f(128,128,128), 1);
		}

}

