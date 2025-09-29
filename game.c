#include "game.h"
#include "recursos.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <string.h>

bool game_init(Game* game) {
    //se alguma inicialização não funcionar, o jogo não inicia
    if (!al_init()) return false;
    if (!al_install_keyboard()) return false;
    if (!al_init_primitives_addon()) return false;
    if (!al_init_font_addon()) return false;
    if (!al_init_image_addon()) return false;

    //ponteiro que recebe o tamanho do display, fps, fila vazia
    game->display = al_create_display(1280, 720);
    game->timer = al_create_timer(1.0 / 60.0);
    game->queue = al_create_event_queue();



    if (!game->display || !game->timer || !game->queue) return false;

    //registro dos eventos na fila em ordem
    al_register_event_source(game->queue, al_get_display_event_source(game->display));
    al_register_event_source(game->queue, al_get_keyboard_event_source());
    al_register_event_source(game->queue, al_get_timer_event_source(game->timer));

    //informações acima sem problema, o jogo pode rodar
    game->running = true;
    game->redraw = true;

    al_start_timer(game->timer);

    return true;
}

void game_loop(Game* game) {
    //define player
    Player player;
    //posição inicial player
    player_init(&player, 1280 / 2, 700);

    game->guerreiro = criar_sprite("images/guerreiro.png", 2);

    //define array com todas teclas existentes
    unsigned char key[ALLEGRO_KEY_MAX];
    //assegura que nenhuma tecla está pressionada
    memset(key, 0, sizeof(key));

    ALLEGRO_EVENT event;

    while (game->running) {
        al_wait_for_event(game->queue, &event);

        
        switch (event.type) {
            //se o tipo do evento for timer...
        case ALLEGRO_EVENT_TIMER:
            //atualize a tecla que foi pressionada
            player_update(&player, key);
            //atualizar_sprite(game->guerreiro, unsigned char key[]);

            //reseta flag seen das teclas
            for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= ~KEY_SEEN;

            //próximo ciclo
            game->redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            //verifica qual tecla foi pressionada nesse ciclo
            key[event.keyboard.keycode] = KEY_SEEN | KEY_DOWN;
            //evento de fechar janela
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                game->running = false;
            break;

            //verifica tecla que deixou de ser pressionada
        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= ~KEY_DOWN;
            break;

            //se fechar o display jogo para
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            game->running = false;
            break;
        }

        //se não há eventos pendentes na fila 
        if (game->redraw && al_is_event_queue_empty(game->queue)) {
            //limpa a tela primeiro
            al_clear_to_color(al_map_rgb(0, 0, 0));
            desenha_sprite(game->guerreiro);
            //desenha o jogador
            player_draw(&player);
            //troca os displays para não travar ao redesenhar
            al_flip_display();
            game->redraw = false;
        }
    }
}
//destrói tudo para não colapsar memória
void game_shutdown(Game* game) {
    if (game->guerreiro) {
        destruir_sprite(game->guerreiro);
    }
    al_destroy_display(game->display);
    al_destroy_timer(game->timer);
    al_destroy_event_queue(game->queue);
    
}
