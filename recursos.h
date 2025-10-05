#ifndef RECURSOS_H
#define RECURSOS_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

typedef struct {
	ALLEGRO_BITMAP* sheet;
	ALLEGRO_BITMAP** frames;
	int num_frames;
	int frame_atual;
	int frame_largura;
	int frame_altura;
	int x, y;
	int vel_y;
	int flip;
	bool no_chao;
	int cont;
}Sprite;

Sprite* criar_sprite(const char* caminho, int num_frames, int display_width, int display_height, int height_sprite);
void atualizar_sprite(Sprite* guerreiro, unsigned char key[], int display_width, int display_height, int height_sprite);
void desenha_sprite(Sprite* guerreiro, int dx, int dy, int flip);
void destruir_sprite(Sprite* sprite);


#endif