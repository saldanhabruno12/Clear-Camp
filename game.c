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
    if (!al_init()) {
        printf("Erro ao inicializar Allegro\n");
        return -1;
    }

    if (!al_init_image_addon()) {
        printf("Erro ao inicializar addon de imagens\n");
        return -1;
    }

    if (!al_install_keyboard()) {
        printf("Erro ao inicializar teclado\n");
        return -1;
    }

    int tela_largura = 800;
    int tela_altura = 600;
    ALLEGRO_DISPLAY* display = al_create_display(tela_largura, tela_altura);
    if (!display) {
        printf("Erro ao criar display\n");
        return -1;
    }
    al_set_window_title(display, "Jogo");

    ALLEGRO_EVENT_QUEUE* fila = al_create_event_queue();
    if (!fila) {
        al_destroy_display(display);
        return -1;
    }

    // Registrar eventos
    al_register_event_source(fila, al_get_display_event_source(display));
    al_register_event_source(fila, al_get_keyboard_event_source());

    ALLEGRO_BITMAP* fundo = al_load_bitmap("mapa_grecia.png");
    if (!fundo) {
        printf("Erro ao carregar imagem\n");
        al_destroy_event_queue(fila);
        al_destroy_display(display);
        return -1;
    }

    // Dimensões da imagem
    int img_largura = al_get_bitmap_width(fundo);
    int img_altura = al_get_bitmap_height(fundo);

    float escala_x = (float)tela_largura / img_largura;
    float escala_y = (float)tela_altura / img_altura;
    float escala_final = (escala_x < escala_y) ? escala_x : escala_y;

    int nova_largura = img_largura * escala_final;
    int nova_altura = img_altura * escala_final;

    int pos_x = (tela_largura - nova_largura) / 2;
    int pos_y = (tela_altura - nova_altura) / 2;

    bool rodando = true;

    while (rodando) {
        // desenhar a tela
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_scaled_bitmap(fundo,
            0, 0, img_largura, img_altura,
            pos_x, pos_y, nova_largura, nova_altura,
            0);
        al_flip_display();

        ALLEGRO_EVENT evento;
        al_wait_for_event(fila, &evento);

        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            rodando = false;
        }
        else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                rodando = false;
            }
        }
    }

    al_destroy_bitmap(fundo);
    al_destroy_event_queue(fila);
    al_destroy_display(display);

    return 0;
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
