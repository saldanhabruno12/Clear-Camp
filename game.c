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

bool game_init(Game* game) {
    if (!al_init()) return false;
    if (!al_install_keyboard()) return false;
    if (!al_install_mouse()) return false;
    if (!al_init_primitives_addon()) return false;
    if (!al_init_font_addon()) return false;
    if (!al_init_image_addon()) return false;
    if (!al_init_ttf_addon()) return false;

    game->display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    game->timer = al_create_timer(1.0 / 60.0);
    game->queue = al_create_event_queue();
    game->ato = ATO1;
	game->etapa_ato1 = ETAPA_ATO1_0;
    game->etapa_ato2 = ETAPA_ATO2_0;
    game->etapa_ato3 = ETAPA_ATO3_0;
    game->estado_game = MENU;
    game->cenario = al_load_bitmap("images/menu.jpeg");
    game->fonte_menu = al_load_ttf_font("fonts/menu/MedievalSharp.ttf", 60, 0);
    game->pergaminho = al_load_bitmap("dialogo_ato1.png");
    game->planotroia = al_load_bitmap("dialogo_ato2.png");
    game->fonte_dialogo = al_load_ttf_font("fonts/menu/MedievalSharp.ttf", 32, 0);
    game->fonte_contexto = al_load_ttf_font("fonts/menu/MedievalSharp.ttf", 28, 0);
    game->fonte_pular = al_load_ttf_font("fonts/menu/MedievalSharp.ttf", 26, 0);

    game->contexto = al_load_bitmap("narrador.png");

    if (!game->pergaminho || !game->fonte_dialogo) {
        printf("Erro ao carregar recursos de di logo.\n");
        return false;
    }

    if (!game->display || !game->timer || !game->queue) return false;

    al_register_event_source(game->queue, al_get_display_event_source(game->display));
    al_register_event_source(game->queue, al_get_keyboard_event_source());
    al_register_event_source(game->queue, al_get_mouse_event_source());
    al_register_event_source(game->queue, al_get_timer_event_source(game->timer));
    
    float mouse_x = 0 , mouse_y = 0;

    game->cavalo = criar_entidade(cavalo, SCREEN_WIDTH, SCREEN_HEIGHT, 300, SCREEN_WIDTH / 2 - 300, 594, 0);
    game->cavaleiro = criar_entidade(cavaleiro, SCREEN_WIDTH, SCREEN_HEIGHT, 84, SCREEN_WIDTH / 2 - 300, 594, 0);
    definir_hitbox(game->cavaleiro, 25, 22, 32, 32);
    game->boss = criar_inimigo(boss, SCREEN_WIDTH, SCREEN_HEIGHT, 64, SCREEN_WIDTH / 2, 624, 1);
    definir_hitbox(game->boss->infos, 12, 0, 47, 47);


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
            break;

        case CONTEXTO:
            break;

        case DIALOGO:
            break;

        case JOGANDO2:
            if (key[ALLEGRO_KEY_ESCAPE]) {
                mudar_cenario(game, "images/menu.jpeg");
                mudanca_estado(game, MENU);
            }
            break;

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
    if (caminho == "images/menu/menu.png") {
        al_draw_text(game->fonte_menu, al_map_rgb(255, 255, 255), 620, 620, ALLEGRO_ALIGN_CENTER, "COMO JOGAR");
        al_draw_text(game->fonte_menu, al_map_rgb(255, 255, 255), 630, 500, ALLEGRO_ALIGN_CENTER, "OPCOES");
        al_draw_text(game->fonte_menu, al_map_rgb(255, 255, 255), 630, 370, ALLEGRO_ALIGN_CENTER, "INICIAR");
    }
    if (!game->cenario)
        printf("Erro ao carregar novo cenario: %s\n", caminho);
}

void desenhar_menu(Game* game, int largura, int altura) {
    desenhar_cenario(game->cenario, largura, altura);
    if (!game->fonte_menu) {
        printf("Erro ao carregar fonte");
        return -1;
    }
    al_draw_text(game->fonte_menu, al_map_rgb(255, 255, 255), 620, 620, ALLEGRO_ALIGN_CENTER, "COMO JOGAR");
    al_draw_text(game->fonte_menu, al_map_rgb(255, 255, 255), 630, 500, ALLEGRO_ALIGN_CENTER, "OPCOES");
    al_draw_text(game->fonte_menu, al_map_rgb(255, 255, 255), 630, 370, ALLEGRO_ALIGN_CENTER, "INICIAR");

}

void desenhar_contexto(Game* game, int largura, int altura) {
    desenhar_cenario(game->contexto, largura, altura);
    if (!game->fonte_menu) {
        printf("Erro ao carregar fonte");
        return -1;
    }
    al_draw_text(game->fonte_contexto, al_map_rgb(0, 0, 0), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 170, ALLEGRO_ALIGN_CENTER, "Na cidade de Esparta, celebrava-se o casamento entre Menelau, rei de Esparta,");
    al_draw_text(game->fonte_contexto, al_map_rgb(0, 0, 0), 615, SCREEN_HEIGHT / 2 + 200, ALLEGRO_ALIGN_CENTER, "e Helena, filha de Zeus. Durante a cerimonia, Helena foi raptada por Paris,");
    al_draw_text(game->fonte_contexto, al_map_rgb(0, 0, 0), 615, SCREEN_HEIGHT / 2 + 230, ALLEGRO_ALIGN_CENTER, "principe de Troia, que a levou para sua cidade. Tomado pela furia, Menelau");
    al_draw_text(game->fonte_contexto, al_map_rgb(0, 0, 0), 620, SCREEN_HEIGHT / 2 + 260, ALLEGRO_ALIGN_CENTER, "convocou os reis e Aquiles, o mais forte guerreiro, para resgatar sua esposa.");

    al_draw_text(game->fonte_pular, al_map_rgb(255, 255, 255),
        960, SCREEN_HEIGHT / 2 + 290,
        ALLEGRO_ALIGN_CENTER, "Pressione ENTER para continuar");
}

void desenhar_narrador(Game* game, int largura, int altura) {
    desenhar_cenario(game->contexto, largura, altura);
    if (!game->fonte_menu) {
        printf("Erro ao carregar fonte");
        return -1;
    }

    al_draw_text(game->fonte_pular, al_map_rgb(255, 255, 255),
        960, SCREEN_HEIGHT / 2 + 290,
        ALLEGRO_ALIGN_CENTER, "Pressione ENTER para continuar");

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
    default:
        break;
    }

    al_draw_text(game->fonte_dialogo, al_map_rgb(255, 255, 255),
        SCREEN_WIDTH / 2, SCREEN_HEIGHT - 40,
        ALLEGRO_ALIGN_CENTER, "Pressione ENTER para continuar");

    al_flip_display();

}

void game_loop(Game* game) {
    //define player
    //Player player;
    //posição inicial player
    //player_init(&player, SCREEN_WIDTH / 2, 700);



    //define array com todas teclas existentes

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    ALLEGRO_EVENT event;

    while (game->running) {
        al_wait_for_event(game->queue, &event);

        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
            check_input(game, key, event);

            //atualize a tecla que foi pressionada
            //atualizar_sprite(game->guerreiro, unsigned char key[]);
            switch (game->estado_game) {
                case MENU:
					break;

				case CONTEXTO:
                    break;

				case DIALOGO:
                    break;

                case JOGANDO:
                    atualizar_inimigo(game->boss, game->cavaleiro);
                    atualizar_entidade(game->cavaleiro, game->boss->infos, key, SCREEN_WIDTH, SCREEN_HEIGHT, 84);
                    //printf("HP = %d / %d\n", game->boss->infos->hp, game->boss->infos->hp_max);
                    atualizar_hitbox(game->boss->infos);
                    if (game->cavaleiro->x > 1280) trocar_mapa(game, 1);
                    if (game->cavaleiro->x < -50) trocar_mapa(game, -1);
                    if (game->cavaleiro->hp <= 0) {
                        printf("Jogador morreu! Avançando para o Ato 2...\n");
                        game->ato = ATO2;                
                        mudanca_estado(game, NARRADOR);
                        reiniciar_entidade(game->cavaleiro);
                        reiniciar_entidade(game->boss->infos);
                    }
                    break;

                case NARRADOR:
                    break;


                case DIALOGO2:
                    break;

                case JOGANDO2:
                    atualizar_entidade(game->cavalo, game->boss->infos, key, SCREEN_WIDTH, SCREEN_HEIGHT, 300);
                    atualizar_inimigo(game->boss, game->cavaleiro);
                    atualizar_entidade(game->cavaleiro, game->boss->infos, key, SCREEN_WIDTH, SCREEN_HEIGHT, 84);
                    //printf("HP = %d / %d\n", game->boss->infos->hp, game->boss->infos->hp_max);
                    atualizar_hitbox(game->boss->infos);
                    if (game->cavaleiro->x > 1280) trocar_mapa(game, 1);
                    if (game->cavaleiro->x < -50) trocar_mapa(game, -1);
                    if (game->cavaleiro->hp <= 0) {
                        mudar_cenario(game, "images/menu.jpeg");
                        mudanca_estado(game, MENU);
                    }
                    break;
                    
            }

            for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= ~KEY_SEEN;

            game->redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event.keyboard.keycode] = KEY_SEEN | KEY_DOWN;

            if (game->estado_game == DIALOGO) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    switch (game->ato) {
                    case ATO1:
                        game->etapa_ato1++;
                        if (game->etapa_ato1 == NEXT_ATO1) {
							mudar_cenario(game, "mapa_grecia.png");
                            mudanca_estado(game, JOGANDO);
                        }
                        break;
                    case ATO2:
                        game->etapa_ato2++;
                        if (game->etapa_ato2 == NEXT_ATO2) {
                            mudar_cenario(game, "mapa_grecia.png");
                            mudanca_estado(game, NARRADOR);
                        }
                    }
                }
            }

            if (game->estado_game == NARRADOR) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    switch (game->ato) {
                    case ATO2:
                        game->etapa_ato2++;
                        if (game->etapa_ato2 == NEXT_ATO2) {
                            mudanca_estado(game, DIALOGO2);
                            game->ato = ATO3;
                        }
                        break;
                    }
                }
            }

            if (game->estado_game == DIALOGO2) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    switch (game->ato) {
                    case ATO3:
                        game->etapa_ato3++;
                        if (game->etapa_ato3 == NEXT_ATO3) {
                            mudar_cenario(game, "mapa__esparta.png");
                            mudanca_estado(game, JOGANDO2);
                        }
                        break;
                    }
                }
            }
            
            // ESC fecha o jogo no menu
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE && game->estado_game == MENU) {
                game->running = false;
            }

            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && game->estado_game == MENU) {
                mudanca_estado(game, CONTEXTO);
            }

            
            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && game->estado_game == CONTEXTO) {
                mudanca_estado(game, DIALOGO);
            }

            // ESC no jogo ? volta ao menu
            else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE && game->estado_game == JOGANDO) {
                mudar_cenario(game, "images/menu.jpeg");
                mudanca_estado(game, MENU);
            }

            else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE && game->estado_game == DIALOGO2) {
                desenhar_dialogo_ulisses(game);
            }

            break;

        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= ~KEY_DOWN;
            break;

        case ALLEGRO_EVENT_MOUSE_AXES:
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

                case CONTEXTO:
                    desenhar_contexto(game, SCREEN_WIDTH, SCREEN_HEIGHT);
					break;

                case NARRADOR:
                    desenhar_narrador(game, SCREEN_WIDTH, SCREEN_HEIGHT);
                    break;

                    case DIALOGO:
                    desenhar_dialogo(game);
					break;
    
                case JOGANDO:
                    desenhar_cenario(game->cenario, SCREEN_WIDTH, SCREEN_HEIGHT);
                    desenhar_inimigo(game->boss, 2.5);
                    desenhar_hitbox(game->cavaleiro);
                    desenhar_entidade(game->cavaleiro, 2.0);//cavaleiro
                    desenhar_hitbox(game->boss->infos);
                    desenhar_hp_fixa(game->cavaleiro, 20, 20, false);
                    desenhar_hp_fixa(game->boss->infos, SCREEN_WIDTH - 400 - 20, 20, true);
					break;

                case DIALOGO2:
                    desenhar_dialogo_ulisses(game);
                    break;
                case JOGANDO2:
                    desenhar_cenario(game->cenario, SCREEN_WIDTH, SCREEN_HEIGHT);
                    desenhar_inimigo(game->boss, 2.5);
                    desenhar_hitbox(game->cavaleiro);
                    desenhar_entidade(game->cavalo, 0.5);
                    desenhar_entidade(game->cavaleiro, 2.0);
                    desenhar_hitbox(game->boss->infos);
                    desenhar_hp_fixa(game->cavaleiro, 20, 20, false);
                    desenhar_hp_fixa(game->boss->infos, SCREEN_WIDTH - 400 - 20, 20, true);
                    break;
            }

            al_flip_display();
            game->redraw = false;
        }
    }
}


void game_shutdown(Game* game) {
    if (game->cenario) {
        destruir_cenario(game->cenario);
    }
    if (game->pergaminho) al_destroy_bitmap(game->pergaminho);
    if (game->fonte_dialogo) al_destroy_font(game->fonte_dialogo);
    al_destroy_display(game->display);
    al_destroy_timer(game->timer);
    al_destroy_event_queue(game->queue);
    destruir_entidade(game->cavaleiro);
    destruir_inimigo(game->boss);
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

    // Destr i o cen rio atual
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
        //game->boss->x = 0;
    }
    else
        game->cavaleiro->x = 1280 - 100;
}