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
#include "ato.h"
#include "entidade.h"

void desenhar_menu(Game* game, int largura, int altura, const char* caminho) {
    desenhar_cenario(game->cenario, largura, altura);
    if (!game->fonte_menu) {
        printf("Erro ao carregar fonte");
        return -1;
    }
    if (caminho == "images/menu/menu_correto.png") {
        al_draw_text(game->fonte_menu, al_map_rgb(255, 255, 255), 620, 620, ALLEGRO_ALIGN_CENTER, "COMO JOGAR");
        al_draw_text(game->fonte_menu, al_map_rgb(255, 255, 255), 630, 500, ALLEGRO_ALIGN_CENTER, "INICIAR");
    }

}

void desenhar_narrador(Game* game, int largura, int altura) {
    desenhar_cenario(game->contexto, largura, altura);
    if (!game->fonte_menu) {
        printf("Erro ao carregar fonte");
        return -1;
    }

    al_draw_text(game->fonte_pular, al_map_rgb(0, 0, 0),
        960, SCREEN_HEIGHT / 2 + 290,
        ALLEGRO_ALIGN_CENTER, "Pressione ENTER para continuar");

    switch (game->ato) {
    case ATO0:
        iniciar_ato0(game->fonte_dialogo, game->etapa_ato0);
        break;
    case ATO1:
        iniciar_ato1(game->fonte_dialogo, game->etapa_ato1);
        break;
    case ATO2:
        iniciar_ato2(game->fonte_dialogo, game->etapa_ato2);
        break;
    case ATO3:
        iniciar_ato3(game->fonte_dialogo, game->etapa_ato3);
        break;
    case ATO4:
        iniciar_ato4(game->fonte_dialogo, game->etapa_ato4);
        break;
    case ATO5:
        iniciar_ato5(game->fonte_dialogo, game->etapa_ato5);
        break;
    default:
        break;
    }

}

void desenhar_dialogo(Game* game) {
    static bool iniciou = false;
    static bool dialogo_concluido = false;

    al_clear_to_color(al_map_rgb(0, 0, 0));

    float perg_larg = al_get_bitmap_width(game->pergaminho);
    float perg_alt = al_get_bitmap_height(game->pergaminho);

    // desenha o pergaminho ocupando a tela inteira
    al_draw_scaled_bitmap(
        game->pergaminho,
        0, 0, perg_larg, perg_alt,  // origem (imagem original)
        0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,  // destino (preencher a tela)
        0
    );

    switch (game->ato) {
    case ATO1:
        iniciar_ato1(game->fonte_dialogo, game->etapa_ato1);
        break;
    case ATO2:
        iniciar_ato2(game->fonte_dialogo, game->etapa_ato2);
        break;
    case ATO3:
        iniciar_ato3(game->fonte_dialogo, game->etapa_ato3);
        break;
    default:
        break;
    }

    al_draw_text(game->fonte_dialogo, al_map_rgb(255, 255, 255),
        SCREEN_WIDTH / 2, SCREEN_HEIGHT - 40,
        ALLEGRO_ALIGN_CENTER, "Pressione ENTER para continuar");

    al_flip_display();

}

void desenhar_dialogo_ulisses(Game* game) {
    static bool iniciou = false;
    static bool dialogo_concluido = false;

    al_clear_to_color(al_map_rgb(0, 0, 0));

    float perg_larg = al_get_bitmap_width(game->planotroia);
    float perg_alt = al_get_bitmap_height(game->planotroia);


    al_draw_scaled_bitmap(
        game->planotroia,
        0, 0, perg_larg, perg_alt,
        0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
        0
    );

    switch (game->ato) {
    case ATO1:
        iniciar_ato1(game->fonte_dialogo, game->etapa_ato1);
        break;
    case ATO2:
        iniciar_ato2(game->fonte_dialogo, game->etapa_ato2);
        break;
    case ATO3:
        iniciar_ato3(game->fonte_dialogo, game->etapa_ato3);
        break;
    case ATO4:
        iniciar_ato4(game->fonte_dialogo, game->etapa_ato4);
        break;

    default:
        break;
    }

    al_draw_text(game->fonte_dialogo, al_map_rgb(255, 255, 255),
        SCREEN_WIDTH / 2, SCREEN_HEIGHT - 40,
        ALLEGRO_ALIGN_CENTER, "Pressione ENTER para continuar");

    al_flip_display();

}

void desenhar_dialogo_final(Game* game) {
    static bool iniciou = false;
    static bool dialogo_concluido = false;

    al_clear_to_color(al_map_rgb(0, 0, 0));

    float perg_larg = al_get_bitmap_width(game->dialogofinal);
    float perg_alt = al_get_bitmap_height(game->dialogofinal);

    // desenha o pergaminho ocupando a tela inteira
    al_draw_scaled_bitmap(
        game->dialogofinal,
        0, 0, perg_larg, perg_alt,  // origem (imagem original)
        0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,  // destino (preencher a tela)
        0
    );

    switch (game->ato) {
    case ATO1:
        iniciar_ato1(game->fonte_dialogo, game->etapa_ato1);
        break;
    case ATO2:
        iniciar_ato2(game->fonte_dialogo, game->etapa_ato2);
        break;
    case ATO3:
        iniciar_ato3(game->fonte_dialogo, game->etapa_ato3);
        break;
    case ATO4:
        iniciar_ato4(game->fonte_dialogo, game->etapa_ato4);
        break;
    case ATO5:
        iniciar_ato5(game->fonte_dialogo, game->etapa_ato5);
        break;
    case ATO6:
        iniciar_ato6(game->fonte_dialogo, game->etapa_ato6);
        break;
    default:
        break;
    }

    al_draw_text(game->fonte_dialogo, al_map_rgb(255, 255, 255),
        SCREEN_WIDTH / 2, SCREEN_HEIGHT - 40,
        ALLEGRO_ALIGN_CENTER, "Pressione ENTER para continuar");

    al_flip_display();

}

void desenhar_final(Game* game, int largura, int altura) {
    desenhar_cenario(game->imagem_final, largura, altura);
    if (!game->fonte_menu) {
        printf("Erro ao carregar fonte");
        return -1;
    }

    al_draw_text(game->fonte_menu, al_map_rgb(255, 255, 255), 630, 370, ALLEGRO_ALIGN_CENTER, "FIM");

}