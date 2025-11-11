#ifndef INIMIGO_H
#define INIMIGO_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include "entidade.h"

typedef enum {
	ESTADO_AGUARDANDO,
	ESTADO_BUSCANDO,
	ESTADO_ATACANDO,
	ESTADO_FUGINDO,
	ESTADO_MORRENDO
} EstadoBot;

typedef struct {
	EstadoBot estado;
	Entidade* infos;
	int direcao;
	int tempo_estado;
} Inimigo;

Inimigo* criar_inimigo(DadosAnimacoes dados, int display_width, int display_height, int altura_personagem, int pos_x, int pos_y, int flip);
void atualizar_inimigo(Inimigo* inimigo, Entidade* jogador);
void desenhar_inimigo(Inimigo* inimigo, int escalonamento);
void destruir_inimigo(Inimigo* inimigo);

#endif