#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

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

}

int main(void){

	int f,c;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_DISPLAY* disp;
	// flag
	bool redraw = true;
	// creamos la variable tipo "union" que
	ALLEGRO_EVENT event;

	setupAllegro(f,c,timer,queue,disp);

	while(1){
		al_wait_for_event(queue, &event);


	}

}

void display_matriz(){

}
