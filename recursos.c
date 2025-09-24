#include "recursos.h"
#include <stdlib.h>

Sprite* criar_sprite(const char* caminho, int num_frames) {
	Sprite* guerreiro = malloc(sizeof(Sprite));
	if (!guerreiro) return NULL;

	guerreiro->sheet = al_load_bitmap(caminho);
	if (!guerreiro->sheet) {
		free(guerreiro);
		return NULL;
	}

	guerreiro->num_frames = num_frames;
	guerreiro->frame_atual = 0;
	guerreiro->cont = 0;
	
	guerreiro->frame_largura = al_get_bitmap_width(guerreiro->sheet) / num_frames;
	guerreiro->frame_altura = al_get_bitmap_height(guerreiro->sheet);

	guerreiro->frames = malloc(sizeof(ALLEGRO_BITMAP*) * num_frames);

	for (int i = 0; i < num_frames; i++) {
		guerreiro->frames[i] = al_create_sub_bitmap(guerreiro->sheet,
			i * guerreiro->frame_largura,
			0,
			guerreiro->frame_largura,
			guerreiro->frame_altura);
	}
	guerreiro->x = 1280 / 2;
	guerreiro->y = 670;

	return guerreiro;
}

void atualizar_sprite(Sprite* guerreiro, unsigned char key[]) {
	if (key[ALLEGRO_KEY_D] || key[ALLEGRO_KEY_RIGHT]) {
		guerreiro->x += 2;
	}
	if (key[ALLEGRO_KEY_A] || key[ALLEGRO_KEY_LEFT]) {
		guerreiro->x -= 2;
	}

	//se o personagem estiver no chão
	if (guerreiro->y >= 670) {
		guerreiro->y = 670;
		guerreiro->vel_y = 0;
		guerreiro->no_chao = true;
	}


	//se pressionar w e estiver no chão, pula
	if (key[ALLEGRO_KEY_W] && guerreiro->no_chao) {
		guerreiro->vel_y = -15;
		guerreiro->no_chao = false;
	}

	//posição vertical e gravidade de queda
	guerreiro->vel_y += 1;
	guerreiro->y += guerreiro->vel_y;
	
	
	guerreiro->cont++;
	if (guerreiro->cont % 10 == 0) {
		guerreiro->frame_atual = (guerreiro->frame_atual + 1) % guerreiro->num_frames;
	}
}

void desenha_sprite(Sprite* guerreiro) {
	al_draw_bitmap(guerreiro->frames[guerreiro->frame_atual], guerreiro->x, guerreiro->y, 0);
}

void destruir_sprite(Sprite* sprite) {
	if (sprite) {
		for (int i = 0; i < sprite->num_frames; i++) {
			if (sprite->frames[i]) {
				al_destroy_bitmap(sprite->frames[i]);
			}
		}
		free(sprite->frames);
		if (sprite->sheet) {
			al_destroy_bitmap(sprite->sheet);
		}
		free(sprite);
	}
}