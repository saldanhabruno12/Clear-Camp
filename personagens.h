#ifndef PERSONAGENS_H
#define PERSONAGENS_H

#include "entidade.h"

typedef struct {
    DadosAnimacoes animacoes;
    DadosHitbox hitbox;
} PersonagemDados;


extern DadosAnimacoes cavaleiro;
extern DadosHitbox cavaleiro_hitbox;

extern DadosAnimacoes boss;
extern DadosHitbox boss_hitbox;

#endif

