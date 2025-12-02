#ifndef ENTIDADE_H
#define ENTIDADE_H
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include "colisao.h"

#define KEY_SEEN 1
#define KEY_DOWN 2

typedef enum {
	ANDANDO, 
	CORRENDO,
	PULANDO,
	ATACANDO,
	MORRENDO,
	PARADO,
	MORTO,
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
	int largura_sprite;
	int altura_sprite;
	int hitbox_offset_x;
	int hitbox_offset_y;
	int hitbox_largura;
	int hitbox_altura;
} DadosHitbox; 

typedef struct {
	Animacao* animacoes[NUM_ACOES];
	Acao acao_atual;
	Hitbox box;
	int frame_atual;
	int cont;
	float x, y;
	float offset_cima, offset_baixo, offset_esquerda, offset_direita;
	float vel_x, vel_y;
	bool no_chao;
	bool ataque_ativo, dano_aplicado;
	int flip;
	int hp, hp_max;
} Entidade;

typedef struct {
	const char* caminhos[NUM_ACOES];
	int linhas[NUM_ACOES];
	int colunas[NUM_ACOES];
	int frames[NUM_ACOES];
} DadosAnimacoes;


Animacao* criar_animacao(const char* caminho, int linhas, int colunas);
Entidade* criar_entidade(DadosAnimacoes dados, int display_width, int display_height, int altura_personagem, int pos_x, int flip, int hp);
void atualizar_hitbox(Entidade* entidade);
void definir_hitbox(Entidade* entidade, float offset_cima, float offset_baixo, float offset_esquerda, float offset_direita);
void atualizar_entidade(Entidade* entidade, Entidade* inimigo, Entidade* capanga, unsigned char key[], int display_width, int display_height, int altura_personagem, int dano, float escala, int fase);
void desenhar_entidade(Entidade* entidade, float escalonamento);
void destruir_entidade(Entidade* entidade);
void desenhar_hitbox(Entidade* entidade);
void aplicar_dano(Entidade* entidade, int dano);
void desenhar_hp_fixa(Entidade* entidade, int tela_x, int tela_y, bool invertida);
void atualizar_ataque(Entidade* atacante, Entidade* alvo, int dano);
void reiniciar_entidade(Entidade* entidade);
//void mudar_acao(Entidade* entidade, Acao nova_acao);
bool colidiu(Entidade* a, Entidade* b);



#endif