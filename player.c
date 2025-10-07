#include "player.h"
#include <stdio.h>
#include <allegro5/allegro_primitives.h>

int escalonamento = 2;

Sprite_cavaleiro* criar_sprite_multiplas_acoes(int display_width, int display_height, int altura_personagem) {
	Sprite_cavaleiro* cavaleiro = malloc(sizeof(Sprite_cavaleiro));
	if (!cavaleiro) return NULL;

	for (int i = 0; i < NUM_ACOES; i++) {
		cavaleiro->animacoes[i] = NULL;
	}

	cavaleiro->animacoes[ANDANDO] = criar_animacao("images/cavaleiro_caminhar.png", 8);
	cavaleiro->animacoes[CORRENDO] = criar_animacao("images/cavaleiro_corrida.png", 8);
	cavaleiro->animacoes[PULANDO] = criar_animacao("images/cavaleiro_pulo.png", 5);
	cavaleiro->animacoes[ATACANDO] = criar_animacao("images/cavaleiro_ataque1.png", 6);
	cavaleiro->animacoes[MORRENDO] = criar_animacao("images/cavaleiro_morte.png", 12);
	cavaleiro->animacoes[PARADO] = criar_animacao("images/cavaleiro_parado.png", 7);

	for (int i = 0; i < NUM_ACOES; i++) {
		if (!cavaleiro->animacoes[i]) {
			printf("falha ao carregar animacao %d" , i);
			destruir_sprite(cavaleiro);
			return NULL;
		}
	}

	cavaleiro->acao_atual = PARADO;
	cavaleiro->frame_atual = 0;
	cavaleiro->cont = 0;
	cavaleiro->x = display_width / 2;
	cavaleiro->y = display_height - altura_personagem * escalonamento;
	cavaleiro->vel_x = 0;
	cavaleiro->vel_y = 0;
	cavaleiro->no_chao = true;
	cavaleiro->flip = 0;
	
	return cavaleiro;
}

Animacao* criar_animacao(const char* caminho, int num_frames) {
	Animacao* anima = malloc(sizeof(Animacao));
	if (!anima) return NULL;

	anima->sheet = al_load_bitmap(caminho);

	if (!anima->sheet) {
		printf("Erro: Não foi possível carregar %s\n", caminho);
		free(anima);
		return NULL;
	}

	anima->num_frames = num_frames;
	anima->frame_largura = al_get_bitmap_width(anima->sheet) / num_frames;
	anima->frame_altura = al_get_bitmap_height(anima->sheet);

	anima->frames = malloc(sizeof(ALLEGRO_BITMAP*) * num_frames);

	if (!anima->frames) {
		al_destroy_bitmap(anima->sheet);
		free(anima);
		return NULL;
	}

	for (int i = 0; i < num_frames; i++) {
		anima->frames[i] = al_create_sub_bitmap(anima->sheet,
			i * anima->frame_largura, 0,
			anima->frame_largura, anima->frame_altura);
	}
	return anima;
}

void mudar_acao(Sprite_cavaleiro* sprite, Acao nova_acao) {
	if (sprite->acao_atual != nova_acao) {
		sprite->acao_atual = nova_acao;
		sprite->frame_atual = 0; 
		sprite->cont = 0;
	}
}

void atualizar_sprite_cavaleiro(Sprite_cavaleiro* sprite, unsigned char key[], int display_width, int display_height, int altura_personagem) {
	bool esta_se_movendo = false;


    // Movimento horizontal
    if (key[ALLEGRO_KEY_D] || key[ALLEGRO_KEY_RIGHT]) {
        sprite->x += 2;
        sprite->flip = 0;
        esta_se_movendo = true;
    }
    if (key[ALLEGRO_KEY_A] || key[ALLEGRO_KEY_LEFT]) {
        sprite->x -= 2;
        sprite->flip = ALLEGRO_FLIP_HORIZONTAL;
        esta_se_movendo = true;
    }

    // Ataque (tem prioridade sobre outros estados)
    if (key[ALLEGRO_KEY_SPACE]) {
        mudar_acao(sprite, ATACANDO);
    }
    // Pulo
    else if (key[ALLEGRO_KEY_W] && sprite->no_chao) {
        sprite->vel_y = -15;
        sprite->no_chao = false;
        mudar_acao(sprite, PULANDO);
    }
    // Movimento horizontal
    else if (esta_se_movendo && sprite->no_chao) {
        mudar_acao(sprite, CORRENDO);
    }
    // Parado (estado padrão)
    else if (sprite->no_chao && sprite->acao_atual != ATACANDO) {
        mudar_acao(sprite, PARADO);
    }

    // Física e limites da tela
    if (sprite->x < 0) sprite->x = 0;
    if (sprite->x > display_width - sprite->animacoes[sprite->acao_atual]->frame_largura * 2) {
        sprite->x = display_width - sprite->animacoes[sprite->acao_atual]->frame_largura * 2;
    }

    // Gravidade e colisão com o chão
    sprite->vel_y += 1;
    sprite->y += sprite->vel_y;

    if (sprite->y >= display_height - altura_personagem * escalonamento) {
        sprite->y = display_height - altura_personagem * escalonamento;
        sprite->vel_y = 0;
        sprite->no_chao = true;

        // Se acabou de cair e não está fazendo outra ação, volta para parado
        if (sprite->acao_atual == PULANDO) {
            mudar_acao(sprite, PARADO);
        }
    }
    else {
        sprite->no_chao = false;
    }

    // Atualização da animação
    sprite->cont++;
    Animacao* anim_atual = sprite->animacoes[sprite->acao_atual];

    // Velocidade de animação diferente para cada ação
    int velocidade_animacao;
    switch (sprite->acao_atual) {
    case CORRENDO: velocidade_animacao = 4; break; // Mais rápido
    case ATACANDO: velocidade_animacao = 6; break; // Mais lento
    case PULANDO: velocidade_animacao = 8; break;  // Mais lento ainda
    default: velocidade_animacao = 10; break;      // PARADO - mais lento
    }

    if (sprite->cont >= velocidade_animacao) {
        sprite->frame_atual = (sprite->frame_atual + 1) % anim_atual->num_frames;
        sprite->cont = 0;

        // Se é uma animação que não loopa (como ataque) e terminou
        if (sprite->acao_atual == ATACANDO && sprite->frame_atual == 0) {
            mudar_acao(sprite, PARADO); // Volta para parado após o ataque
        }
    }
}

void desenhar_sprite(Sprite_cavaleiro* sprite) {
    if (!sprite || !sprite->animacoes[sprite->acao_atual]) return;

    Animacao* anima = sprite->animacoes[sprite->acao_atual];
    ALLEGRO_BITMAP* frame_atual = anima->frames[sprite->frame_atual];

    al_draw_scaled_bitmap(frame_atual,
        0, 0, anima->frame_largura, anima->frame_altura,
        sprite->x, sprite->y,
        anima->frame_largura * escalonamento, anima->frame_altura * escalonamento,
        sprite->flip);
}

void destruir_sprite_cavaleiro(Sprite_cavaleiro* sprite) {
    if (!sprite) return;

    for (int i = 0; i < NUM_ACOES; i++) {
        if (sprite->animacoes[i]) {
            for (int j = 0; j < sprite->animacoes[i]->num_frames; j++) {
                if (sprite->animacoes[i]->frames[j]) {
                    al_destroy_bitmap(sprite->animacoes[i]->frames[j]);
                }
            }
            free(sprite->animacoes[i]->frames);
            if (sprite->animacoes[i]->sheet) {
                al_destroy_bitmap(sprite->animacoes[i]->sheet);
            }
            free(sprite->animacoes[i]);
        }
    }
    free(sprite);
}

