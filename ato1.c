#include "ato1.h"
#include "ui.h"
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
    case ETAPA_0:
        al_draw_text(font, al_map_rgb(255, 255, 255),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
            ALLEGRO_ALIGN_CENTER, "O rei falou");
        break;
    case ETAPA_1:
        al_draw_text(font, al_map_rgb(255, 255, 255),
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
            ALLEGRO_ALIGN_CENTER, "O rei falou2");
        break;
    }
}

