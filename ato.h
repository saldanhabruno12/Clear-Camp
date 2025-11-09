#ifndef ATO_H
#define ATO_H
#include <allegro5/allegro_font.h>

typedef enum {
	ATO1,
	ATO2,
	ATO3
} Ato;

typedef enum {
	ETAPA_ATO1_0,
	ETAPA_ATO1_1,
	ETAPA_ATO1_2,
	ETAPA_ATO1_3,
	NEXT_ATO1
} EtapaAto1;

typedef enum {
	ETAPA_ATO2_0,
	ETAPA_ATO2_1,
	ETAPA_ATO2_2,
	ETAPA_ATO2_3,
	NEXT_ATO2
} EtapaAto2;

typedef enum {
	ETAPA_ATO3_0,
	ETAPA_ATO3_1,
	ETAPA_ATO3_2,
	ETAPA_ATO3_3,
	NEXT_ATO3
} EtapaAto3;

void iniciar_ato1(ALLEGRO_FONT* font, EtapaAto1 etapa);
void iniciar_ato2(ALLEGRO_FONT* font, EtapaAto2 etapa);
void iniciar_ato3(ALLEGRO_FONT* font, EtapaAto3 etapa);


#endif





