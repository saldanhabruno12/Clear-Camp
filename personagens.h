#ifndef PERSONAGENS_H
#define PERSONAGENS_H

#include "entidade.h"

typedef struct {
    DadosAnimacoes animacoes;
    DadosHitbox hitbox;
} PersonagemDados;


extern DadosAnimacoes capanga;
extern DadosHitbox capanga_hitbox;

extern DadosAnimacoes patroclo;
extern DadosHitbox patroclo_hitbox;

extern DadosAnimacoes menelau;
extern DadosHitbox menelau_hitbox;

extern DadosAnimacoes cavaleiro;
extern DadosHitbox cavaleiro_hitbox;

extern DadosAnimacoes boss;
extern DadosHitbox boss_hitbox;

extern DadosAnimacoes cavalo;

#endif

