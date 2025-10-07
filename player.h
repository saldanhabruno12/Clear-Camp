#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>

#define KEY_SEEN 1
#define KEY_DOWN 2

typedef enum {
	ANDANDO,
	CORRENDO,
	PULANDO,
	ATACANDO,
	MORRENDO,
	PARADO,
	NUM_ACOES
} Acao;

typedef struct {
	ALLEGRO_BITMAP* sheet;
	ALLEGRO_BITMAP** frames;
	int num_frames;
	int frame_largura;
	int frame_altura;
} Animacao;

typedef struct {
	Animacao* animacoes[NUM_ACOES];
	Acao acao_atual;
	int frame_atual;
	int cont;
	float x, y;
	float vel_x, vel_y;
	bool no_chao;
	int flip;
} Sprite_cavaleiro;

Sprite_cavaleiro* criar_sprite_multiplas_acoes(int display_width, int display_height, int altura_personagem);
Animacao* criar_animacao(const char* caminho, int num_frames);
void atualizar_sprite_cavaleiro(Sprite_cavaleiro* sprite, unsigned char key[], int display_width, int display_height, int altura_personagem);
void desenhar_sprite(Sprite_cavaleiro* sprite);
void destruir_sprite_cavaleiro(Sprite_cavaleiro* sprite);
void mudar_acao(Sprite_cavaleiro* sprite, Acao nova_acao);

#endif