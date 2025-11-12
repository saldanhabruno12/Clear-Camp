#include "entidade.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>

static void mudar_acao(Entidade* entidade, Acao nova_acao);

Entidade* criar_entidade(DadosAnimacoes dados, int display_width, int display_height, int altura_personagem, int pos_x, int flip) {
	Entidade* entidade = malloc(sizeof(Entidade));
	if (!entidade) return NULL;

	for (int i = 0; i < NUM_ACOES; i++) {
		entidade->animacoes[i] = NULL;
	}

	for (int i = 0; i < NUM_ACOES; i++) {
		if (dados.caminhos[i]) {
			entidade->animacoes[i] = criar_animacao(dados.caminhos[i], dados.linhas[i], dados.colunas[i]);
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
	entidade->x = pos_x;
	entidade->y = display_height - altura_personagem * 1.5;
	entidade->vel_x = 0;
	entidade->vel_y = 0;
	entidade->no_chao = true;
	entidade->flip = flip;
	entidade->hp_max = 100;
	entidade->hp = entidade->hp_max;

	return entidade;
}

void definir_hitbox(Entidade* entidade, float offset_cima, float offset_baixo, float offset_esquerda, float offset_direita) {
	entidade->offset_cima = offset_cima;
	entidade->offset_baixo = offset_baixo;
	entidade->offset_direita = offset_direita;
	entidade->offset_esquerda = offset_esquerda;
	atualizar_hitbox(entidade);
}


static Animacao* criar_animacao(const char* caminho, int linhas, int colunas) {
	Animacao* anima = malloc(sizeof(Animacao));
	if (!anima) return NULL;

	anima->sheet = al_load_bitmap(caminho);
	if (!anima->sheet) {
		printf("Erro ao carregar %s\n", caminho);
		free(anima);
		return NULL;
	}

	anima->num_frames = colunas * linhas;
	anima->frame_largura = al_get_bitmap_width(anima->sheet) / colunas;
	anima->frame_altura = al_get_bitmap_height(anima->sheet) / linhas;
	anima->frames = malloc(sizeof(ALLEGRO_BITMAP*) * anima->num_frames);

	for (int i = 0; i < anima->num_frames; i++) {
		int coluna = i % colunas;
		int linha = i / colunas;

		anima->frames[i] = al_create_sub_bitmap(anima->sheet,
			coluna * anima->frame_largura, linha * anima->frame_altura,
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

void atualizar_hitbox(Entidade* entidade) {
	Animacao* animacao = entidade->animacoes[entidade->acao_atual];

	if (!animacao) {
		animacao = entidade->animacoes[PARADO];
		if (!animacao) return;
	}
	
	entidade->box.x = entidade->x + entidade->offset_esquerda * 2;
	entidade->box.y = entidade->y + entidade->offset_cima * 2;
	entidade->box.w = (entidade->animacoes[entidade->acao_atual]->frame_largura - (entidade->offset_esquerda + entidade->offset_direita)) * 2;
	entidade->box.h = (entidade->animacoes[entidade->acao_atual]->frame_altura - (entidade->offset_cima + entidade->offset_baixo)) * 2;

}

void desenhar_hitbox(Entidade* entidade) {
	float x1, x2, y1, y2;

	x1 = entidade->box.x;
	y1 = entidade->box.y;
	x2 = x1 + entidade->box.w;
	y2 = y1 + entidade->box.h;

	al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(255, 0, 0), 1.0);
}


void atualizar_entidade(Entidade* entidade, Entidade* inimigo, unsigned char key[], int display_width, int display_height, int altura_personagem) {
	bool movendo = false;
	atualizar_hitbox(entidade);
	entidade->vel_x = 2;
	if (key[ALLEGRO_KEY_D] && entidade->hp > 0 || key[ALLEGRO_KEY_RIGHT] && entidade->hp > 0) {
		entidade->x += entidade->vel_x;
		entidade->flip = 0;
		movendo = true;
	}
	if (key[ALLEGRO_KEY_A] && entidade->hp > 0 || key[ALLEGRO_KEY_LEFT] && entidade->hp > 0) {
		entidade->x -= entidade->vel_x;
		entidade->flip = ALLEGRO_FLIP_HORIZONTAL;
		movendo = true;
	}

	if (key[ALLEGRO_KEY_SPACE] && entidade->hp > 0) {
		mudar_acao(entidade, ATACANDO);
		atualizar_ataque(entidade, inimigo, 10);
	}
	else if ((key[ALLEGRO_KEY_W] && entidade->no_chao && entidade->hp > 0 || key[ALLEGRO_KEY_UP]) && entidade->no_chao && entidade->hp > 0) {
		entidade->vel_y = -15;
		entidade->no_chao = false;
		mudar_acao(entidade, PULANDO);
	}
	else if (movendo && entidade->no_chao && entidade->hp > 0) {
		mudar_acao(entidade, CORRENDO);
	}
	else if (entidade->no_chao && entidade->acao_atual != ATACANDO && entidade->hp > 0) {
		mudar_acao(entidade, PARADO);
	}
	else if (entidade->hp <= 0 && entidade->acao_atual != MORRENDO) {
		int frame_final = entidade->animacoes[MORRENDO]->num_frames - 1;
		entidade->hp = 0;
		mudar_acao(entidade, MORRENDO);
	}

	entidade->vel_y += 1;
	entidade->y += entidade->vel_y;

	if (entidade->y >= display_height - altura_personagem * 1.5) {
		entidade->y = display_height - altura_personagem * 1.5;
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
	case MORRENDO: velocidade_animacao = 10; break;
	default: velocidade_animacao = 10; break;      // PARADO - mais lento
	}
	
	if (entidade->acao_atual == MORRENDO && entidade->frame_atual == entidade->animacoes[MORRENDO]->num_frames - 1) return;

	if (entidade->cont >= velocidade_animacao) {
		entidade->frame_atual = (entidade->frame_atual + 1) % anim_atual->num_frames;
		entidade->cont = 0;

		// Se é uma animação que não loopa (como ataque) e terminou
		if (entidade->acao_atual == ATACANDO && entidade->frame_atual == 0) {
			mudar_acao(entidade, PARADO); // Volta para parado após o ataque
		}
	}
}

void aplicar_dano(Entidade* entidade, int dano) {
	entidade->hp -= dano;
	if (entidade->hp <= 0) {
		entidade->hp = 0;
	}
}

void atualizar_ataque(Entidade* atacante, Entidade* alvo, int dano) {
	if (atacante->acao_atual == ATACANDO) {
		int frame_final = atacante->animacoes[ATACANDO]->num_frames - 1;

		if (atacante->frame_atual == frame_final && !atacante->dano_aplicado) {
			if (colidiu(atacante, alvo)) {
				aplicar_dano(alvo, dano);
				atacante->dano_aplicado = true;
			}
		}
		if (atacante->frame_atual == 0) {
			atacante->dano_aplicado = false;
		}
	}
}

void desenhar_hp_fixa(Entidade* entidade, int tela_x, int tela_y, bool invertida) {
	float barra_largura = 400.0;
	float barra_altura = 20.0;

	float hp_porcentagem = (float)entidade->hp / entidade->hp_max;
	float hp_barra = barra_largura * hp_porcentagem;


	if (invertida) {
		al_draw_filled_rectangle(
			tela_x, tela_y,
			tela_x + barra_largura, tela_y + barra_altura,
			al_map_rgb(0, 200, 0)
		);
		int r = 200;
		int g = 0;
		al_draw_filled_rectangle(
			tela_x + (barra_largura - hp_barra), tela_y,
			tela_x + barra_largura , tela_y + barra_altura,
			al_map_rgb(r, g, 0)
		);
	}
	else {
		al_draw_filled_rectangle(
			tela_x, tela_y,
			tela_x + barra_largura, tela_y + barra_altura,
			al_map_rgb(120, 0, 0)
		);
		al_draw_filled_rectangle(
			tela_x, tela_y,
			tela_x + hp_barra, tela_y + barra_altura,
			al_map_rgb(0, 200, 0)
		);
	}

	al_draw_rectangle(
		tela_x, tela_y,
		tela_x + barra_largura, tela_y + barra_altura,
		al_map_rgb(0, 0, 0),
		2.0
	);
}

void reiniciar_entidade(Entidade* entidade) {
	entidade->hp = 100;
}



bool colidiu(Entidade* a, Entidade* b) {
	return (
		a->box.x < b->box.x + b->box.w &&
		a->box.x + a->box.w > b->box.x &&
		a->box.y < b->box.y + b->box.h &&
		a->box.y + a->box.h > b->box.y 
		);
}


void desenhar_entidade(Entidade* entidade, float escalonamento) {
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
			for (int j = 0; j < entidade->animacoes[i]->num_frames; j++) al_destroy_bitmap(entidade->animacoes[i]->frames[j]);
			free(entidade->animacoes[i]->frames);
			al_destroy_bitmap(entidade->animacoes[i]->sheet);
			free(entidade->animacoes[i]);
		}
	}
	free(entidade);
}


