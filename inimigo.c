#include "inimigo.h"
#include <stdlib.h>
#include <stdio.h>

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

void atualizar_inimigo(Inimigo* inimigo, Entidade* jogador) {
	inimigo->tempo_estado++;

	switch (inimigo->estado) {
	case ESTADO_AGUARDANDO:
		mudar_acao(inimigo->infos, PARADO);

		if (distancia(inimigo, jogador) <= 50) {//zona de captacao
			inimigo->estado = ESTADO_BUSCANDO;
			inimigo->tempo_estado = 0;

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

		inimigo->infos->x += inimigo->direcao * 2;

		//verifica direcao errada
		if ((jogador->x > inimigo->infos->x && inimigo->direcao == -1) || (jogador->x < inimigo->infos->x && inimigo->direcao == 1)) {
			inimigo->direcao *= -1;
			inimigo->infos->flip = !inimigo->infos->flip;
		}


		if (jogador->x - inimigo->infos->x > 100) {
			inimigo->estado = ESTADO_AGUARDANDO;
			inimigo->tempo_estado = 0;
			inimigo->direcao *= -1;

			if (distancia(inimigo, jogador) <= 15) {
				inimigo->estado = ESTADO_ATACANDO;
				inimigo->tempo_estado = 0;
			}
			break;

	case ESTADO_ATACANDO:
		mudar_acao(inimigo->infos, ATACANDO);
		if (distancia(inimigo, jogador) > 20) {
			inimigo->estado = ESTADO_BUSCANDO;
			inimigo->tempo_estado = 0;
		}
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
		if (inimigo->infos->cont >= 6) {
			inimigo->infos->frame_atual = (inimigo->infos->frame_atual + 1) % anim->num_frames;
			inimigo->infos->cont = 0;
		}

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
	return sqrt(pow((inimigo->infos->x - jogador->x), 2) + pow((inimigo->infos->y - jogador->y), 2));
}