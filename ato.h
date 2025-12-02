#ifndef ATO_H
#define ATO_H
#include <allegro5/allegro_font.h>

typedef enum {
	ATO0,
	ATO1,
	ATO2,
	ATO3,
	ATO4,
	ATO5,
	ATO6
} Ato;

typedef enum {
	ETAPA_ATO0_0,
	ETAPA_ATO0_1,
	ETAPA_ATO0_2,
	ETAPA_ATO0_3,
	ETAPA_ATO0_4,
	ETAPA_ATO0_5,
	NEXT_ATO0
} EtapaAto0;

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

typedef enum {
	ETAPA_ATO4_0,
	ETAPA_ATO4_1,
	ETAPA_ATO4_2,
	ETAPA_ATO4_3,
	ETAPA_ATO4_4,
	ETAPA_ATO4_5,
	ETAPA_ATO4_6,
	ETAPA_ATO4_7,
	ETAPA_ATO4_8,
	NEXT_ATO4
} EtapaAto4;

typedef enum {
	ETAPA_ATO5_0,
	ETAPA_ATO5_1,
	ETAPA_ATO5_2,
	ETAPA_ATO5_3,
	NEXT_ATO5
} EtapaAto5;

typedef enum {
	ETAPA_ATO6_0,
	ETAPA_ATO6_1,
	ETAPA_ATO6_2,
	ETAPA_ATO6_3,
	ETAPA_ATO6_4,
	ETAPA_ATO6_5,
	NEXT_ATO6
} EtapaAto6;

void iniciar_ato0(ALLEGRO_FONT* font, EtapaAto0 etapa);
void iniciar_ato1(ALLEGRO_FONT* font, EtapaAto1 etapa);
void iniciar_ato2(ALLEGRO_FONT* font, EtapaAto2 etapa);
void iniciar_ato3(ALLEGRO_FONT* font, EtapaAto3 etapa);
void iniciar_ato4(ALLEGRO_FONT* font, EtapaAto4 etapa);
void iniciar_ato5(ALLEGRO_FONT* font, EtapaAto5 etapa);
void iniciar_ato6(ALLEGRO_FONT* font, EtapaAto6 etapa);

#endif





