#ifndef DIALOGO_H
#define DIALOGO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

typedef struct {
	const char* texto;
	ALLEGRO_BITMAP* retrato;

} Dialogo;

void desenhar_dialogo(Dialogo* dialogo, ALLEGRO_FONT* fonte, int largura_tela, int altura_tela);

#endif