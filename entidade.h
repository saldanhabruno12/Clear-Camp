#ifndef ENTIDADE_H
#define ENTIDADE_H

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
} Entidade;

typedef struct {
	const char* caminhos[NUM_ACOES];
	int linhas[NUM_ACOES];
	int colunas[NUM_ACOES];
	int frames[NUM_ACOES];
} DadosAnimacoes;

Entidade* criar_entidade(DadosAnimacoes dados, int display_width, int display_height, int altura_personagem, int pos_x, int flip);
void atualizar_entidade(Entidade* entidade, unsigned char key[], int display_width, int display_height, int altura_personagem);
void desenhar_entidade(Entidade* entidade, int escalonamento);
void destruir_entidade(Entidade* entidade);

#endif