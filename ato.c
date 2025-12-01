#include "ato.h"
#include <allegro5/allegro.h>
#include "game.h"
#include "recursos.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <string.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <stdbool.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

void iniciar_ato1(ALLEGRO_FONT* font, EtapaAto1 etapa) {
    switch (etapa) {
    case ETAPA_ATO1_0:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, 120,
            ALLEGRO_ALIGN_CENTER, "Aquiles, minha esposa Helena foi raptada...");
        break;
    case ETAPA_ATO1_1:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, 120,
            ALLEGRO_ALIGN_CENTER, "Paris a levou para a cidade de Troia");
        break;
    case ETAPA_ATO1_2:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, 120,
            ALLEGRO_ALIGN_CENTER, "Avise todos os reis gregos e junte os exercitos!");
        break;
    case ETAPA_ATO1_3:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, 120,
            ALLEGRO_ALIGN_CENTER, "Iremos busca-la em Troia!");
    }
}

void iniciar_ato2(ALLEGRO_FONT* font, EtapaAto2 etapa) {
    switch (etapa) {
    case ETAPA_ATO2_0:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "Os gregos dominaram os pequenos vilareijos");
        break;
    case ETAPA_ATO2_1:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "Ao dividirem os tesouros conquistados");
        break;
    case ETAPA_ATO2_2:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "Agammenon o lider do exercito grego entra em conflito com Aquiles");
        break;
    case ETAPA_ATO2_3:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "Mesmo estando do mesmo lado, os dois travam uma batalha!");
    }
}

void iniciar_ato3(ALLEGRO_FONT* font, EtapaAto3 etapa) {
    switch (etapa) {
    case ETAPA_ATO3_0:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "Aquiles perdeu seu duelo contra Agammenon");
        break;
    case ETAPA_ATO3_1:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "Apos ser derrotado, Aquiles se retirou da guerra");
        break;
    case ETAPA_ATO3_2:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "Patroclo, amigo de Aquiles, ira lutar em seu lugar");
        break;
    case ETAPA_ATO3_3:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "Agammenon e Patroclo continuam rumo a troia");
    }
}

void iniciar_ato4(ALLEGRO_FONT* font, EtapaAto4 etapa) {
    switch (etapa) {
    case ETAPA_ATO4_0:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "O plano do Cavalo de Troia de Ulisses foi um sucessso");
        break;
    case ETAPA_ATO4_1:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "Os gregos sairam de dentro do cavalo");
        break;
    case ETAPA_ATO4_2:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "e venceram a guerra. Aquiles vingou seu amigo");
        break;
    case ETAPA_ATO4_3:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "A princessa Helena foi enfim resgatda");
    }
}


void iniciar_ato5(ALLEGRO_FONT* font, EtapaAto5 etapa) {
    switch (etapa) {
    case ETAPA_ATO5_0:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, 120,
            ALLEGRO_ALIGN_CENTER, "Esstou feliz em te-la de volta");
        break;
    case ETAPA_ATO5_1:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, 120,
            ALLEGRO_ALIGN_CENTER, "Aquiles conseguiu se vingar");
        break;
    case ETAPA_ATO5_2:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, 120,
            ALLEGRO_ALIGN_CENTER, "Troia caiu diante o plano de Ulisses");
        break;
    case ETAPA_ATO5_3:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, 120,
            ALLEGRO_ALIGN_CENTER, "Eu declaria guerra ao mundo");
        break;
    case ETAPA_ATO5_4:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, 120,
            ALLEGRO_ALIGN_CENTER, "para te ter novamente...");
        break;
    case ETAPA_ATO5_5:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, 120,
            ALLEGRO_ALIGN_CENTER, "e foi isso que eu fiz!");
    }

}


