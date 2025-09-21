#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro5.h>

#define KEY_SEEN 1
#define KEY_DOWN 2

//definição da posição inicial do jogador
typedef struct {
    int x, y;
    int vel_y;
    bool no_chao;
} Player;

//inicializa posição do jogador
void player_init(Player* p, int start_x, int start_y);
//atualiza a posição do jogador de acordo com a interação
void player_update(Player* p, unsigned char key[]);
//desenha o jogador de acordo com as posições das funções anteriores
void player_draw(Player* p);

#endif
