#include "player.h"
#include <allegro5/allegro_primitives.h>

//posições iniciais do jogador
void player_init(Player* p, int start_x, int start_y) {
    p->x = start_x;
    p->y = start_y;
}

//novas posições conforme clique
void player_update(Player* p, unsigned char key[]) {
    if (key[ALLEGRO_KEY_D] || key[ALLEGRO_KEY_RIGHT]) {
        p->x += 2;
    }
    if (key[ALLEGRO_KEY_A] || key[ALLEGRO_KEY_LEFT]) {
        p->x -= 2;
    }

    //se o personagem estiver no chão
    if (p->y >= 700) {
        p->y = 700;
        p->vel_y = 0;
        p->no_chao = true;
    }


    //se pressionar w e estiver no chão, pula
    if (key[ALLEGRO_KEY_W] && p->no_chao) {
        p->vel_y = -15;
        p->no_chao = false;
    }

    //posição vertical e gravidade de queda
    p->vel_y += 1;
    p->y += p->vel_y;

}

//desenha jogador nas posições definidas e na cor desejada
void player_draw(Player* p) {
    al_draw_filled_circle(p->x, p->y, 20, al_map_rgb(255, 0, 255));
}
