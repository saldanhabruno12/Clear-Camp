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
            ALLEGRO_ALIGN_CENTER, "Ao chegarem perto de Troia, Patroclo enfrenta Heitor");
        break;
    case ETAPA_ATO2_1:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "Em uma batalha epica, Patroclo morre.");
        break;
    case ETAPA_ATO2_2:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "Mesmo assim, os gregos dominam os vilarejos vizinhos");
        break;
    case ETAPA_ATO2_3:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "e montam seus acampamentos sob o comando de Agamemnon.");
    }
}

void iniciar_ato3(ALLEGRO_FONT* font, EtapaAto2 etapa) {
    switch (etapa) {
    case ETAPA_ATO3_0:
        al_draw_text(font, al_map_rgb(255, 255, 255),
            200, SCREEN_HEIGHT / 2 - 170,
            ALLEGRO_ALIGN_CENTER, "Ulisses avise Aquiles que Patroclo morreu.");
        break;
    case ETAPA_ATO3_1:
        al_draw_text(font, al_map_rgb(255, 255, 255),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 170,
            ALLEGRO_ALIGN_CENTER, "Precisamos que ele volte a guerra.");
        break;
    case ETAPA_ATO3_2:
        al_draw_text(font, al_map_rgb(255, 255, 255),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 170,
            ALLEGRO_ALIGN_CENTER, "E traga-me um plano para invadir a cidade de Troia.");
        break;
    case ETAPA_ATO3_3:
        al_draw_text(font, al_map_rgb(255, 255, 255),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
            ALLEGRO_ALIGN_CENTER, "O plebeu falou");
    }
}


