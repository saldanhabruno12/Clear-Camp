#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include "recursos.h"
#include "cenario.h"
#include "estado.h"
#include "entidade.h"
#include "personagens.h"
#include "inimigo.h"
#include "ato.h"
#include "click.h"
#include "cavalo.h"
#include "capanga.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct Game {
    ALLEGRO_DISPLAY* display;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    bool running;
    bool redraw;
    Sprite* guerreiro;
    ALLEGRO_BITMAP* cenario;
    Estado_game estado_game;
    ALLEGRO_FONT* fonte_menu;
    ALLEGRO_BITMAP* pergaminho;
	ALLEGRO_BITMAP* dialogofinal;
	ALLEGRO_BITMAP* contexto;    
    ALLEGRO_FONT* fonte_dialogo;
    ALLEGRO_FONT* fonte_contexto;
    ALLEGRO_FONT* fonte_pular;
	ALLEGRO_BITMAP* planotroia;
	ALLEGRO_BITMAP* imagem_final;
    int mapa_atual;
    bool aguardando_enter;
    Entidade* cavaleiro;
    Inimigo* boss;
    Inimigo* capanga;
    float mouse_x, mouse_y;
    Retangulo iniciar, opcoes, como_jogar;
    Cavalo* cavalo;
    Ato ato;
    EtapaAto1 etapa_ato1;
    EtapaAto2 etapa_ato2;
    EtapaAto3 etapa_ato3;
    EtapaAto4 etapa_ato4;
    EtapaAto4 etapa_ato5;
} Game;


bool game_init(Game* game);

void mudanca_estado(Game* game, Estado_game estado_game);
void game_loop(Game* game);
void game_shutdown(Game* game);
void mudar_cenario(Game* game, const char* caminho);
void trocar_mapa(Game* game, int direcao);
void desenhar_dialogo(Game* game);

#endif
