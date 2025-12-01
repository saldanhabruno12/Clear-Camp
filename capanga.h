#ifndef CAPANGA_H
#define CAPANGA_H

#include "inimigo.h"

void atualizar_capanga(Inimigo* inimigo, Entidade* jogador, int dano);
void desenhar_capanga(Entidade* entidade, float escalonamento, int fase);

#endif 