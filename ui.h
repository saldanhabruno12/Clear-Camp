#ifndef UI_H
#define UI_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

void desenhar_caixa_dialogo(ALLEGRO_BITMAP* pergaminho, ALLEGRO_FONT* fonte, const char* texto);
void texto_animado(ALLEGRO_BITMAP* pergaminho, ALLEGRO_FONT* fonte, const char* texto, float velocidade);

#endif
