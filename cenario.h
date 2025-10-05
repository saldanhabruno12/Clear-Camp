#ifndef CENARIO_H
#define CENARIO_H

#include <allegro5/allegro.h>

ALLEGRO_BITMAP* carregar_cenario(const char* caminho);
void desenhar_cenario(ALLEGRO_BITMAP* mapa, int tela_largura, int tela_altura);
void destruir_cenario(ALLEGRO_BITMAP* mapa);

#endif
