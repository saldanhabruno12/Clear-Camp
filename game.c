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
#include "ato1.h"

bool game_init(Game* game) {
    if (!al_init()) return false;
    if (!al_install_keyboard()) return false;
    if (!al_init_primitives_addon()) return false;
    if (!al_init_font_addon()) return false;
    if (!al_init_image_addon()) return false;
    if (!al_init_ttf_addon()) return false;

    game->display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    game->timer = al_create_timer(1.0 / 60.0);
    game->queue = al_create_event_queue();
	game->etapa.etapa_atual = ETAPA_0;

    game->estado_game = MENU;
    game->cenario = al_load_bitmap("images/menu.jpeg");
    game->fonte_menu = al_load_ttf_font("fonts/menu/MedievalSharp.ttf", 60, 0);

    
    game->pergaminho = al_load_bitmap("dialogo_ato1.png");
    game->fonte_dialogo = al_load_ttf_font("fonts/menu/MedievalSharp.ttf", 32, 0);

    if (!game->pergaminho || !game->fonte_dialogo) {
        printf("Erro ao carregar recursos de diálogo.\n");
        return false;
    }


    if (!game->display || !game->timer || !game->queue) return false;

    al_register_event_source(game->queue, al_get_display_event_source(game->display));
    al_register_event_source(game->queue, al_get_keyboard_event_source());
    al_register_event_source(game->queue, al_get_timer_event_source(game->timer));

    game->running = true;
    game->redraw = true;

    // carregar cenario

    game->mapa_atual = 1;
   
 

    al_start_timer(game->timer);
    return true;
}
void mudanca_estado(Game* game, Estado_game estado_game) {
    game->estado_game = estado_game;
}
void check_input(Game* game, unsigned char* key, ALLEGRO_EVENT evento) {
    switch (game->estado_game) {
    case MENU:
        
      

    case DIALOGO:
       
        

    case JOGANDO:
        if (key[ALLEGRO_KEY_ESCAPE]) {
            mudar_cenario(game, "images/menu.jpeg");
            mudanca_estado(game, MENU);
        }
        break;
    }
}

void mudar_cenario(Game* game, const char* caminho) {
    if (game->cenario) {
        al_destroy_bitmap(game->cenario);
    }
    game->cenario = al_load_bitmap(caminho);
    if (!game->cenario)
        printf("Erro ao carregar novo cenario: %s\n", caminho);
}

void desenhar_menu(Game* game, int largura, int altura) {
    desenhar_cenario(game->cenario, largura, altura);
    if (!game->fonte_menu) {
        printf("Erro ao carregar fonte");
        return -1;
    }
    al_draw_text(game->fonte_menu, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, ALLEGRO_ALIGN_CENTER, "PRESSIONE ENTER PARA INICIAR");

}

void desenhar_dialogo(Game* game) {
    static bool iniciou = false;
    static int ato_atual = 1;
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

    switch (ato_atual) {
    case 1:
        iniciar_ato1(game->fonte_dialogo, game->etapa.etapa_atual);
        break;
    default:
        
        break;
    }

    // Texto de instrução
    al_draw_text(game->fonte_dialogo, al_map_rgb(255, 255, 255),
        SCREEN_WIDTH / 2, SCREEN_HEIGHT - 40,
        ALLEGRO_ALIGN_CENTER, "Pressione ENTER para continuar");

    al_flip_display();

}



void game_loop(Game* game) {
    // Inicializa entidades e sprites
    game->cavaleiro = criar_entidade(cavaleiro, SCREEN_WIDTH, SCREEN_HEIGHT, 84, SCREEN_WIDTH / 2 - 300, 0);
    game->boss = criar_entidade(boss, SCREEN_WIDTH, SCREEN_HEIGHT, 64, SCREEN_WIDTH / 2, 1);
    game->guerreiro = criar_sprite("images/guerreiro.png", 2, SCREEN_WIDTH, SCREEN_HEIGHT, 51);

    // Array de teclas
    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    ALLEGRO_EVENT event;

    while (game->running) {
        al_wait_for_event(game->queue, &event);

        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
            check_input(game, key, event);

            switch (game->estado_game) {
            case MENU:
             
                break;

            case DIALOGO:
               
                break;

            case JOGANDO:
                atualizar_entidade(game->boss, key, SCREEN_WIDTH, SCREEN_HEIGHT, 64);
                atualizar_entidade(game->cavaleiro, key, SCREEN_WIDTH, SCREEN_HEIGHT, 84);
                atualizar_sprite(game->guerreiro, key, SCREEN_WIDTH, SCREEN_HEIGHT, 54);
                if (game->cavaleiro->x > 1280) trocar_mapa(game, 1);
                if (game->cavaleiro->x < -50) trocar_mapa(game, -1);
                break;
            }

            for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= ~KEY_SEEN;

            game->redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event.keyboard.keycode] = KEY_SEEN | KEY_DOWN;

            if(game->estado_game == DIALOGO) { 
                if(event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    // Avança para o próximo ato ou conclui o diálogo
                    if (game->etapa.etapa_atual == ETAPA_0) {
                        game->etapa.etapa_atual = ETAPA_1;
                    } else {
                        // Diálogo concluído, muda para o estado JOGANDO
                        mudar_cenario(game, "images/mapa_grecia.png");
                        mudanca_estado(game, JOGANDO);
                    }
				}
            }

            // ESC fecha o jogo no menu
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE && game->estado_game == MENU) {
                game->running = false;
            }

            // ENTER no MENU ? vai para o diálogo
            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && game->estado_game == MENU) {
                mudanca_estado(game, DIALOGO);
            }

            // ESC no jogo ? volta ao menu
            else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE && game->estado_game == JOGANDO) {
                mudar_cenario(game, "images/menu.jpeg");
                mudanca_estado(game, MENU);
            }

            break;

        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= ~KEY_DOWN;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            game->running = false;
            break;
        }

        // --- DESENHO ---
        if (game->redraw && al_is_event_queue_empty(game->queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            switch (game->estado_game) {
            case MENU:
                desenhar_menu(game, SCREEN_WIDTH, SCREEN_HEIGHT);
                break;

            case DIALOGO:
                desenhar_dialogo(game);
                break;

            case JOGANDO:
                desenhar_cenario(game->cenario, SCREEN_WIDTH, SCREEN_HEIGHT);
                desenha_sprite(game->guerreiro, SCREEN_WIDTH / 2, 500, game->guerreiro->flip);
                desenhar_entidade(game->cavaleiro, 2);
                desenhar_entidade(game->boss, 2);
                break;
            }

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
    if (game->pergaminho) al_destroy_bitmap(game->pergaminho);
    if (game->fonte_dialogo) al_destroy_font(game->fonte_dialogo);
    al_destroy_display(game->display);
    al_destroy_timer(game->timer);
    al_destroy_event_queue(game->queue);
    destruir_entidade(game->cavaleiro);
    destruir_entidade(game->boss);
}

void trocar_mapa(Game* game, int direcao) {
    const char* mapas[] = {
        "mapa_grecia.png",
        "mapa__esparta.png",
        "mapa_acampamento.png",
        "mapa_porto.png",
        "mapa_castelo.png"

    };
    const int total_mapas = sizeof(mapas) / sizeof(mapas[0]);

    game->mapa_atual += direcao;

    if (game->mapa_atual < 0)
        game->mapa_atual = 0;
    if (game->mapa_atual >= total_mapas)
        game->mapa_atual = total_mapas - 1;

    // Destrói o cenário atual
    if (game->cenario) {
        destruir_cenario(game->cenario);
        game->cenario = NULL;
    }

    // Carrega o novo mapa pelo nome
    const char* caminho = mapas[game->mapa_atual];
    game->cenario = carregar_cenario(caminho);

    if (!game->cenario) {
        printf("Erro ao carregar %s\n", caminho);
    }
    else {
        printf("Mapa carregado: %s\n", caminho);
    }

    // Reposiciona o cavaleiro
    if (direcao > 0) {
        game->cavaleiro->x = 0;
        game->boss->x = 0;
        game->guerreiro->x = 0;
    }
    else
        game->cavaleiro->x = 1280 - 100;
}


