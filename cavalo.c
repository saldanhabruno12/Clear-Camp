#include "cavalo.h"


Cavalo* criar_cavalo(DadosAnimacoes dados, int display_width, int display_height, int altura_personagem, int pos_x, int flip) {
	Cavalo* cavalo = malloc(sizeof(Cavalo));
	if (!cavalo) return NULL;

	cavalo->infos = criar_entidade(dados, display_width, display_height, altura_personagem, pos_x, flip);
	cavalo->infos->y = 450;

	return cavalo;
}

void atualizar_cavalo(Cavalo* cavalo, unsigned char key[], int display_width, int display_height) {
	bool movendo = false;
	cavalo->infos->vel_x = 2;

	if (key[ALLEGRO_KEY_D] || key[ALLEGRO_KEY_RIGHT]) {
		cavalo->infos->x += cavalo->infos->vel_x;
		cavalo->infos->flip = 0;
		movendo = true;
	}

	if (key[ALLEGRO_KEY_A] || key[ALLEGRO_KEY_LEFT]) {
		cavalo->infos->x -= cavalo->infos->vel_x;
		cavalo->infos->flip = ALLEGRO_FLIP_HORIZONTAL;
		movendo = true;
	}

	cavalo->infos->cont++;
	Animacao* anim_atual = cavalo->infos->animacoes[cavalo->infos->acao_atual];

	// Velocidade de animação diferente para cada ação
	int velocidade_animacao;
	switch (cavalo->infos->acao_atual) {
	case CORRENDO: velocidade_animacao = 4; break; // Mais rápido
	case ATACANDO: velocidade_animacao = 6; break; // Mais lento
	case PULANDO: velocidade_animacao = 8; break;  // Mais lento ainda
	case MORRENDO: velocidade_animacao = 10; break;
	default: velocidade_animacao = 10; break;      // PARADO - mais lento
	}


}

void desenhar_cavalo(Cavalo* cavalo, int escalonamento) {
	if (!cavalo || !cavalo->infos->animacoes[cavalo->infos->acao_atual]) return;

	Animacao* anima = cavalo->infos->animacoes[cavalo->infos->acao_atual];
	ALLEGRO_BITMAP* frame = anima->frames[cavalo->infos->frame_atual];

	al_draw_scaled_bitmap(frame, 0, 0, anima->frame_largura, anima->frame_altura,
		cavalo->infos->x, cavalo->infos->y, anima->frame_largura * escalonamento,
		anima->frame_altura * escalonamento, cavalo->infos->flip);

}


void destruir_cavalo(Cavalo* cavalo) {
	if (!cavalo) return;
	for (int i = 0; i < NUM_ACOES; i++) {
		if (cavalo->infos->animacoes[i]) {
			for (int j = 0; j < cavalo->infos->animacoes[i]->num_frames; j++) al_destroy_bitmap(cavalo->infos->animacoes[i]->frames[j]);
			free(cavalo->infos->animacoes[i]->frames);
			al_destroy_bitmap(cavalo->infos->animacoes[i]->sheet);
			free(cavalo->infos->animacoes[i]);
		}
	}
	free(cavalo);
}

