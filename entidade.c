#include "entidade.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>

static Animacao* criar_animacao(const char* caminho, int num_frames);
static void mudar_acao(Entidade* entidade, Acao nova_acao);

Entidade* criar_entidade(DadosAnimacoes dados, int display_width, int display_height, int altura_personagem) {
	Entidade* entidade = malloc(sizeof(Entidade));
	if (!entidade) return NULL;

	for (int i = 0; i < NUM_ACOES; i++) {
		entidade->animacoes[i] = NULL;
	}

	for (int i = 0; i < NUM_ACOES; i++) {
		if (dados.caminhos[i]) {
			entidade->animacoes[i] = criar_animacao(dados.caminhos[i], dados.frames[i]);
			if (!entidade->animacoes[i]) {
				printf("Falha ao carregar animação %d\n", i);
				destruir_entidade(entidade);
				return NULL;
			}
		}
	}

	entidade->acao_atual = PARADO;
	entidade->frame_atual = 0;
	entidade->cont = 0;
	entidade->x = display_width / 2;
	entidade->y = display_height - altura_personagem * 2;
	entidade->vel_x = 0;
	entidade->vel_y = 0;
	entidade->no_chao = true;
	entidade->flip = 0;

	return entidade;
}

static Animacao* criar_animacao(const char* caminho, int num_frames) {
	Animacao* anima = malloc(sizeof(Animacao));
	if (!anima) return NULL;

	anima->sheet = al_load_bitmap(caminho);
	if (!anima->sheet) {
		printf("Erro ao carregar %s\n", caminho);
		free(anima);
		return NULL;
	}

	anima->num_frames = num_frames;
	anima->frame_largura = al_get_bitmap_width(anima->sheet) / num_frames;
	anima->frame_altura = al_get_bitmap_height(anima->sheet);
	anima->frames = malloc(sizeof(ALLEGRO_BITMAP*) * num_frames);

	for (int i = 0; i < num_frames; i++) {
		anima->frames[i] = al_create_sub_bitmap(anima->sheet,
			i * anima->frame_largura, 0,
			anima->frame_largura, anima->frame_altura);
	}

	return anima;
}

static void mudar_acao(Entidade* entidade, Acao nova_acao) {
	if (entidade->acao_atual != nova_acao) {
		entidade->acao_atual = nova_acao;
		entidade->frame_atual = 0;
		entidade->cont = 0;
	}
}

void atualizar_entidade(Entidade* entidade, unsigned char key[], int display_width, int display_height, int altura_personagem) {
	bool movendo = false;

	if (key[ALLEGRO_KEY_D] || key[ALLEGRO_KEY_RIGHT]) {
		entidade->x += 2;
		entidade->flip = 0;
		movendo = true;
	}
	if (key[ALLEGRO_KEY_A] || key[ALLEGRO_KEY_LEFT]) {
		entidade->x -= 2;
		entidade->flip = ALLEGRO_FLIP_HORIZONTAL;
		movendo = true;
	}

	if (key[ALLEGRO_KEY_SPACE]) {
		mudar_acao(entidade, ATACANDO);
	}
	else if ((key[ALLEGRO_KEY_W] && entidade->no_chao || key[ALLEGRO_KEY_UP]) && entidade->no_chao) {
		entidade->vel_y = -15;
		entidade->no_chao = false;
		mudar_acao(entidade, PULANDO);
	}
	else if (movendo && entidade->no_chao) {
		mudar_acao(entidade, CORRENDO);
	}
	else if (entidade->no_chao && entidade->acao_atual != ATACANDO) {
		mudar_acao(entidade, PARADO);
	}

	entidade->vel_y += 1;
	entidade->y += entidade->vel_y;

	if (entidade->y >= display_height - altura_personagem * 2) {
		entidade->y = display_height - altura_personagem * 2;
		entidade->vel_y = 0;
		entidade->no_chao = true;
		if (entidade->acao_atual == PULANDO) {
			mudar_acao(entidade, PARADO);
		}
	}

	entidade->cont++;
	Animacao* anim_atual = entidade->animacoes[entidade->acao_atual];

	// Velocidade de animação diferente para cada ação
	int velocidade_animacao;
	switch (entidade->acao_atual) {
	case CORRENDO: velocidade_animacao = 4; break; // Mais rápido
	case ATACANDO: velocidade_animacao = 6; break; // Mais lento
	case PULANDO: velocidade_animacao = 8; break;  // Mais lento ainda
	default: velocidade_animacao = 10; break;      // PARADO - mais lento
	}

	if (entidade->cont >= velocidade_animacao) {
		entidade->frame_atual = (entidade->frame_atual + 1) % anim_atual->num_frames;
		entidade->cont = 0;

		// Se é uma animação que não loopa (como ataque) e terminou
		if (entidade->acao_atual == ATACANDO && entidade->frame_atual == 0) {
			mudar_acao(entidade, PARADO); // Volta para parado após o ataque
		}
	}
}

void desenhar_entidade(Entidade* entidade, int escalonamento) {
	if (!entidade || !entidade->animacoes[entidade->acao_atual]) return;
	
	Animacao* anima = entidade->animacoes[entidade->acao_atual];
	ALLEGRO_BITMAP* frame = anima->frames[entidade->frame_atual];

	al_draw_scaled_bitmap(frame, 0, 0, anima->frame_largura, anima->frame_altura,
		entidade->x, entidade->y, anima->frame_largura * escalonamento,
		anima->frame_altura * escalonamento, entidade->flip);
}

void destruir_entidade(Entidade* entidade) {
	if (!entidade) return;
	for (int i = 0; i < NUM_ACOES; i++) {
		if (entidade->animacoes[i]) {
			for (int j = 0; j < entidade->animacoes[i]->num_frames; j++)
				al_destroy_bitmap(entidade->animacoes[i]->frames[j]);
			free(entidade->animacoes[i]->frames);
			al_destroy_bitmap(entidade->animacoes[i]->sheet);
			free(entidade->animacoes[i]);
		}
	}
	free(entidade);
}


