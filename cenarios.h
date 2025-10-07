#ifndef CENARIOS_H
#define CENARIOS_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

typedef struct {
	ALLEGRO_BITMAP* mapa;
	int mapa_largura;
	int mapa_altura;
}Cenario;

Cenario* criar_cenario(const char* caminho);
void destruir_cenario(Cenario* mapa);
void desenhar_cenario(const char* mapa, int img_largura, int img_altura, int pos_x, int pos_y, int nova_largura, int nova_altura);


#endif