#ifndef CAVALO_H
#define CAVALO_H
#include "entidade.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>


typedef struct {
	Entidade* infos;
	int direcao;
	int tempo_estado;
} Cavalo;


Cavalo* criar_cavalo(DadosAnimacoes dados, int display_width, int display_height, int altura_personagem, int pos_x, int flip, int hp);
void atualizar_cavalo(Cavalo* cavalo, unsigned char key[], int display_width, int display_height);
void desenhar_cavalo(Cavalo* cavalo, int escalonamento);
void destruir_cavalo(Cavalo* cavalo);


#endif