#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "capanga.h"

static void mudar_acao(Entidade* entidade, Acao nova_acao);


void mudar_acao(Entidade* entidade, Acao nova_acao) {
    if (entidade->acao_atual != nova_acao) {
        entidade->acao_atual = nova_acao;
        entidade->frame_atual = 0;
        entidade->cont = 0;
    }
}

void desenhar_capanga(Entidade* entidade, float escalonamento, int fase) {
    if (!entidade || !entidade->animacoes[entidade->acao_atual]) return;

    Animacao* anima = entidade->animacoes[entidade->acao_atual];
    ALLEGRO_BITMAP* frame = anima->frames[entidade->frame_atual];

    int offset_x = 0, offset_y = 0;

    if (entidade->acao_atual == ATACANDO) {
        if (entidade->flip == 1) {
            offset_x = -75;
            offset_y = -70;
        }
        else {
            offset_x = 30;
            offset_y = -70;
        }
    }
    al_draw_scaled_bitmap(frame, 0, 0, anima->frame_largura, anima->frame_altura,
        entidade->x + offset_x, entidade->y + offset_y, anima->frame_largura * escalonamento,
        anima->frame_altura * escalonamento, entidade->flip);
}


void atualizar_capanga(Inimigo* inimigo, Entidade* jogador, int dano) {
	bool movendo = false;

    atualizar_hitbox(inimigo->infos);

    switch (inimigo->estado) {
    case ESTADO_AGUARDANDO:
        mudar_acao(inimigo->infos, PARADO);
        // Sempre se move
        if (distancia(inimigo, jogador) <= 1500) {
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
        if(!colidiu(inimigo->infos, jogador)) inimigo->infos->x = nova_pos;

        if (colidiu(inimigo->infos, jogador)) {
            inimigo->estado = ESTADO_ATACANDO;
        }
        break;

    case ESTADO_ATACANDO:
        if (jogador->hp > 0) {
            mudar_acao(inimigo->infos, ATACANDO);
            atualizar_ataque(inimigo->infos, jogador, dano);
        }
        else mudar_acao(inimigo->infos, PARADO);

        if (distancia(inimigo, jogador) >= 100) inimigo->estado = ESTADO_AGUARDANDO;

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

    if (inimigo->infos->y >= 640) {
        inimigo->infos->y = 640;
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




