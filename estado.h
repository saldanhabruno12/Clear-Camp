#ifndef ESTADO_H
#define ESTADO_H

#include <allegro5/allegro5.h>


typedef enum {
	MENU,
	JOGANDO,
	DIALOGO,
	CONTEXTO,
	NARRADOR,
	DIALOGO2,
	JOGANDO2,
	GAME_OVER,
	COMO_JOGAR,
	TRANSICAO
} Estado_game;	


#endif