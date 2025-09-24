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
	bool no_chao;
	int cont;
}Sprite;

Sprite* criar_sprite(const char* caminho, int num_frames);
void atualizar_sprite(Sprite* guerreiro, unsigned char key[]);
void desenha_sprite(Sprite* guerreiro);
void destruir_sprite(Sprite* sprite);


#endif