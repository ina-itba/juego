#ifndef DEFINE_GENERAL_H1
#define DEFINE_GENERAL_H1

#include "define_general.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>


void avance_generaciones (char* salir, void* pmatriz, char* mataux, int size, char * pall); //prototipo de función encargada de copiar en una matriz de entrada el resultado del avance de tantas generaciones determinadas
void display_matriz(char* p, int tamanofila);

#endif

