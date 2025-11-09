#ifndef COLISAO_H
#define COLISAO_H

#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>


typedef struct {
	float x, y, w, h;
} Hitbox;

bool colidiu(Hitbox a, Hitbox b);
void desenhar_hitbox(Hitbox hb, ALLEGRO_COLOR cor);

#endif