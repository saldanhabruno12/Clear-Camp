#include "game.h"
#include "recursos.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <string.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <stdbool.h>
#include <allegro5/allegro_image.h>

bool game_init(Game* game) {
    if (!al_init()) return false;
    if (!al_install_keyboard()) return false;
    if (!al_init_primitives_addon()) return false;
    if (!al_init_font_addon()) return false;
    if (!al_init_image_addon()) return false;

    game->display = al_create_display(1280, 720);
    game->timer = al_create_timer(1.0 / 60.0);
    game->queue = al_create_event_queue();

    if (!game->display || !game->timer || !game->queue) return false;

    al_register_event_source(game->queue, al_get_display_event_source(game->display));
    al_register_event_source(game->queue, al_get_keyboard_event_source());
    al_register_event_source(game->queue, al_get_timer_event_source(game->timer));

    game->running = true;
    game->redraw = true;

    // carregar cenario
    game->cenario = carregar_cenario("mapa_grecia.png");
    
    // carregar sprite guerreiro
    game->guerreiro = criar_sprite("images/guerreiro.png", 2);

    al_start_timer(game->timer);
    return true;
}

void game_loop(Game* game) {
    Player player;
    player_init(&player, 1280 / 2, 700);

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    ALLEGRO_EVENT event;

    while (game->running) {
        al_wait_for_event(game->queue, &event);

        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
            player_update(&player, key);

            for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= ~KEY_SEEN;

            game->redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event.keyboard.keycode] = KEY_SEEN | KEY_DOWN;
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                game->running = false;
            break;

        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= ~KEY_DOWN;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            game->running = false;
            break;
        }

        if (game->redraw && al_is_event_queue_empty(game->queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // desenha fundo
            desenhar_cenario(game->cenario, 1280, 720);

            // desenha objetos
            desenha_sprite(game->guerreiro);
            player_draw(&player);

            al_flip_display();
            game->redraw = false;
        }
    }
}

void game_shutdown(Game* game) {
    if (game->guerreiro) {
        destruir_sprite(game->guerreiro);
    }
    if (game->cenario) {
        destruir_cenario(game->cenario);
    }
    al_destroy_display(game->display);
    al_destroy_timer(game->timer);
    al_destroy_event_queue(game->queue);
}