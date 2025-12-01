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

void iniciar_ato0(ALLEGRO_FONT* font, EtapaAto0 etapa) {
    switch (etapa) {
    case ETAPA_ATO0_0:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "Na cidade de Esparta, celebrava-se um grandioso casamento");
        break;
    case ETAPA_ATO0_1:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "entre Menelau, rei de Esparta, e Helena, filha de Zeus.");
        break;
    case ETAPA_ATO0_2:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "Durante a cerimonia Helena foi raptada por Paris");
        break;
    case ETAPA_ATO0_3:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "Paris, o principe de Troia, a levou para sua cidade.");
        break;
    case ETAPA_ATO0_4:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "Tomado pela furia, Menelau convocou os reis gregos");
        break;
    case ETAPA_ATO0_5:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200,
            ALLEGRO_ALIGN_CENTER, "e Aquiles, o mais forte guerreiro, para resgatar sua esposa.");
        break;
    }
}

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
            360, 100,
            ALLEGRO_ALIGN_CENTER, "Ulisses avise Aquiles");
        al_draw_text(font, al_map_rgb(0, 0, 0),
            360, 140,
            ALLEGRO_ALIGN_CENTER, "que Patroclo morreu");
        break;
    case ETAPA_ATO4_1:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            360, 100,
            ALLEGRO_ALIGN_CENTER, "Precisamos que ele");
        al_draw_text(font, al_map_rgb(0, 0, 0),
            360, 140,
            ALLEGRO_ALIGN_CENTER, "volte a guerra");
        break;
    case ETAPA_ATO4_2:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            360, 100,
            ALLEGRO_ALIGN_CENTER, "E traga-me um plano");
        al_draw_text(font, al_map_rgb(0, 0, 0),
            360, 140,
            ALLEGRO_ALIGN_CENTER, "para invadirmos Troia");
        break;
    case ETAPA_ATO4_3:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            920, 100,
            ALLEGRO_ALIGN_CENTER, "Eu tenho um plano Agamemon");
        al_draw_text(font, al_map_rgb(0, 0, 0),
            920, 140,
            ALLEGRO_ALIGN_CENTER, "e Aquiles vai liderar");
        break;
    case ETAPA_ATO4_4:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            920, 100,
            ALLEGRO_ALIGN_CENTER, "Oferecer um enorme cavalo");
        al_draw_text(font, al_map_rgb(0, 0, 0),
            920, 140,
            ALLEGRO_ALIGN_CENTER, "de madeira em forma de paz...");
        break;
    case ETAPA_ATO4_5:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            920, 100,
            ALLEGRO_ALIGN_CENTER, "nossos guerreiros estarao");
        al_draw_text(font, al_map_rgb(0, 0, 0),
            920, 140,
            ALLEGRO_ALIGN_CENTER, "escondidos dentro do cavalo");
        break;
    case ETAPA_ATO4_6:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            920, 100,
            ALLEGRO_ALIGN_CENTER, "invadiremos Troia de");
        al_draw_text(font, al_map_rgb(0, 0, 0),
            920, 140,
            ALLEGRO_ALIGN_CENTER, "dentro para fora");
        break;
    }
}


void iniciar_ato5(ALLEGRO_FONT* font, EtapaAto5 etapa) {
    switch (etapa) {
    case ETAPA_ATO5_0:
        al_draw_text(font, al_map_rgb(0, 0, 0),
            SCREEN_WIDTH / 2, 120,
            ALLEGRO_ALIGN_CENTER, "Estou feliz em te-la de volta");
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


