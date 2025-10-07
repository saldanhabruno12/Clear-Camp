#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro5.h>
#include <stdbool.h>
#include "player.h"
#include "recursos.h"
#include "cenario.h"

typedef struct {
    ALLEGRO_DISPLAY* display;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    bool running;
    bool redraw;
    Sprite* guerreiro;
    Sprite_cavaleiro* cavaleiro;
    ALLEGRO_BITMAP* cenario;
} Game;

bool game_init(Game* game);

void game_loop(Game* game);
void game_shutdown(Game* game);

#endif
