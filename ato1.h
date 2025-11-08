#ifndef ATO1_H
#define ATO1_H
#include <allegro5/allegro_font.h>

typedef enum {
	ETAPA_0,
	ETAPA_1,
	ETAPA_2
} EtapaAto1;

typedef struct {
	EtapaAto1 etapa_atual;
} Ato1;

void iniciar_ato1(ALLEGRO_FONT* font, EtapaAto1 etapa);



#endif




