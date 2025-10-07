#include "cenarios.h"
#include "game.h"
#include <stdlib.h>

Cenario* criar_cenario(const char* caminho) {
	Cenario* mapa = malloc(sizeof(Cenario));

	if (!mapa) return NULL;

	mapa->mapa = al_load_bitmap("images/mapa_guerreiro.png");
	if (!mapa->mapa) {
		free(mapa);
		return NULL;
	}
	//Tamanho original da imagem
	int img_largura = al_get_bitmap_width(mapa);
	int img_altura = al_get_bitmap_height(mapa);

	// Calcular escala mantendo proporção
	float escala_x = (float)1280 / img_largura;
	float escala_y = (float)720 / img_altura;
	float escala_final = (escala_x < escala_y) ? escala_x : escala_y;

	// Dimensões finais da imagem redimensionada
	int nova_largura = img_largura * escala_final;
	int nova_altura = img_altura * escala_final;

	int pos_x = (1280 - nova_largura) / 2;
	int pos_y = (720 - nova_altura) / 2;

	bool rodando = true;

	while (rodando) {

		desenhar_cenario(mapa, img_largura, img_altura, pos_x, pos_y, nova_largura, nova_altura);
	}
}

void desenhar_cenario(const char* mapa, int img_largura, int img_altura, int pos_x, int pos_y, int nova_largura, int nova_altura) {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_scaled_bitmap(mapa,
		0, 0, img_largura, img_altura,
		pos_x, pos_y, nova_largura, nova_altura,
		0);
	al_flip_display();
}

void destruir_cenario(Cenario* mapa) {
	al_destroy_bitmap(mapa);
}
