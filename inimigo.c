#include "inimigo.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static void mudar_acao(Entidade* entidade, Acao nova_acao);
static float distancia(Inimigo* inimigo, Entidade* jogador);

Inimigo* criar_inimigo(DadosAnimacoes dados, int display_width, int display_height, int altura_personagem, int pos_x, int flip) {
	Inimigo* inimigo = malloc(sizeof(Inimigo));
	if (!inimigo) return NULL;
	inimigo->infos = criar_entidade(dados, display_width, display_height, altura_personagem, pos_x, flip);
	inimigo->estado = ESTADO_AGUARDANDO;
	inimigo->direcao = -1;
	inimigo->tempo_estado = 0;
	return inimigo;
}

void atualizar_inimigo(Inimigo* inimigo, Entidade* jogador, int dano) {
	bool movendo = false;

	switch (inimigo->estado) {
    case ESTADO_AGUARDANDO:
        mudar_acao(inimigo->infos, PARADO);
        // Se o jogador estiver perto o suficiente, começa a se mover
        if (distancia(inimigo, jogador) <= 120) {
            inimigo->estado = ESTADO_BUSCANDO;

            // Define direção com base na posição do jogador
            if (jogador->x > inimigo->infos->x) {
                inimigo->direcao = 1;
                inimigo->infos->flip = 0;
            }
            else {
                inimigo->direcao = -1;
                inimigo->infos->flip = 1;
            }
        }
        break;

    case ESTADO_BUSCANDO:
        
        mudar_acao(inimigo->infos, CORRENDO);

        float nova_pos = inimigo->infos->x + inimigo->direcao * 1.5;

        if (nova_pos >= 640 && nova_pos <= 1280) {
            inimigo->infos->x = nova_pos;
        }

        if (distancia(inimigo, jogador) > 150) {
            inimigo->estado = ESTADO_AGUARDANDO;
        }

        if (colidiu(inimigo->infos, jogador)) {
            inimigo->estado = ESTADO_ATACANDO;
        }

        break;

    case ESTADO_ATACANDO:
        if (jogador->hp > 0) {
            mudar_acao(inimigo->infos, ATACANDO);
            atualizar_ataque(inimigo->infos, jogador, dano);
        }
        else {
            mudar_acao(inimigo->infos, PARADO);
        }

        if (!colidiu(inimigo->infos, jogador)) {
            inimigo->estado = ESTADO_AGUARDANDO;
        }
        if (inimigo->infos->hp <= 0) {
            inimigo->infos->hp = 0;
            inimigo->estado = ESTADO_MORRENDO;
        }
        break;

    case ESTADO_MORRENDO:
        mudar_acao(inimigo->infos, MORRENDO);
        break;
}

		inimigo->infos->vel_y += 1;
		inimigo->infos->y += inimigo->infos->vel_y;

		if (inimigo->infos->y >= 590) {
			inimigo->infos->y = 590;
			inimigo->infos->vel_y = 0;
			inimigo->infos->no_chao = true;
		}

		Animacao* anim = inimigo->infos->animacoes[inimigo->infos->acao_atual];
		inimigo->infos->cont++;
        if (inimigo->infos->acao_atual == MORRENDO && inimigo->infos->frame_atual == inimigo->infos->animacoes[MORRENDO]->num_frames - 1) return;

		if (inimigo->infos->cont >= 6) {
			inimigo->infos->frame_atual = (inimigo->infos->frame_atual + 1) % anim->num_frames;
			inimigo->infos->cont = 0;
		}


	}


void desenhar_inimigo(Inimigo* inimigo, int escalonamento) {
	desenhar_entidade(inimigo->infos, escalonamento);
}

void destruir_inimigo(Inimigo* inimigo) {
	destruir_entidade(inimigo->infos);
	free(inimigo);
}

static void mudar_acao(Entidade* entidade, Acao nova_acao) {
	if (entidade->acao_atual != nova_acao) {
		entidade->acao_atual = nova_acao;
		entidade->frame_atual = 0;
		entidade->cont = 0;
	}
}

static float distancia(Inimigo* inimigo, Entidade* jogador) {
	float dx = inimigo->infos->x - jogador->x;
	float dy = inimigo->infos->y - jogador->y;
	float dist2 = dx * dx + dy * dy;
	return sqrtf(dist2);
}

