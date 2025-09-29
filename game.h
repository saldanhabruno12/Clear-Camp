#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro5.h>
#include <stdbool.h>
#include "player.h"
#include "recursos.h"

// definição do esqueleto do jogo
typedef struct {
    ALLEGRO_DISPLAY* display;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    bool running;
    bool redraw;
    Sprite* guerreiro;
} Game;

//verifica se o jogo pode ser iniciado
bool game_init(Game* game);
//loops de eventos de acordo com a interação do usuário
void game_loop(Game* game);
//finalizar execução (fechar o jogo)
void game_shutdown(Game* game);

#endif
