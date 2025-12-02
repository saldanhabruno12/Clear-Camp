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
    game->ato = ATO0;
    game->etapa_ato0 = ETAPA_ATO0_0;
	game->etapa_ato1 = ETAPA_ATO1_0;
    game->etapa_ato2 = ETAPA_ATO2_0;
    game->etapa_ato3 = ETAPA_ATO3_0;
    game->etapa_ato4 = ETAPA_ATO4_0;
    game->etapa_ato5 = ETAPA_ATO5_0;
    game->etapa_ato6 = ETAPA_ATO6_0;
    game->estado_game = MENU;
    game->cenario = al_load_bitmap("images/menu/menu_correto.png");
    game->fonte_menu = al_load_ttf_font("fonts/menu/MedievalSharp.ttf", 35, 0);
    game->pergaminho = al_load_bitmap("dialogo_ato1.png");
    game->dialogofinal = al_load_bitmap("dialogo_final.png");
    game->planotroia = al_load_bitmap("dialogo_ato2.png");
    game->imagem_final = al_load_bitmap("imagem_final.png");
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
    
    game->patroclo = criar_entidade(patroclo, SCREEN_WIDTH, SCREEN_HEIGHT, 135, SCREEN_WIDTH / 2 - 300, 0, 100);
    definir_hitbox(game->patroclo, 15, 12, 33, 33);
    game->cavalo = criar_cavalo(cavalo, SCREEN_WIDTH, SCREEN_HEIGHT, 300, SCREEN_WIDTH / 2 - 200, 0, 10);
    game->cavaleiro = criar_entidade(cavaleiro, SCREEN_WIDTH, SCREEN_HEIGHT, 84, SCREEN_WIDTH / 2 - 300, 0, 100);
    definir_hitbox(game->cavaleiro, 25, 22, 32, 32);
    game->boss = criar_inimigo(boss, SCREEN_WIDTH, SCREEN_HEIGHT, 64, 720, 1, 100);
    definir_hitbox(game->boss->infos, 12, 0, 47, 47);
    game->menelau = criar_inimigo(menelau, SCREEN_WIDTH, SCREEN_HEIGHT, 140, 800, 1, 100);
    game->capanga = criar_inimigo(capanga, SCREEN_WIDTH, SCREEN_HEIGHT, 42, 800, 1, 30);
    definir_hitbox(game->capanga->infos, 5, 3, -20, -20);
    definir_hitbox(game->menelau->infos, 25, 22, 65, 65);


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
            if (key[ALLEGRO_KEY_ENTER]) {
                mudar_cenario(game, "images/mapa_grecia.png");
                mudanca_estado(game, FASE2);
            }
            break;
        
        case COMO_JOGAR:
            if(key[ALLEGRO_KEY_ESCAPE]) {
                mudar_cenario(game, "images/menu/menu.png");
                mudanca_estado(game, MENU);
            }
            break;

        case CONTEXTO:
            if (key[ALLEGRO_KEY_ESCAPE]) {
                mudar_cenario(game, "images/menu/menu.png");
                mudanca_estado(game, MENU);
            }
            break;

        case DIALOGO:
            if (key[ALLEGRO_KEY_ESCAPE]) {
                mudar_cenario(game, "images/menu/menu.png");
                mudanca_estado(game, MENU);
            }
            break;

        case FASE1:
            if (key[ALLEGRO_KEY_ESCAPE]) {
                mudar_cenario(game, "images/menu/menu.png");
                mudanca_estado(game, MENU);
            }
            break;

        case FASE2:
            if (key[ALLEGRO_KEY_ESCAPE]) {
                mudar_cenario(game, "images/menu/menu.png");
                mudanca_estado(game, MENU);
            }
            break;

        case FASE3:
            if (key[ALLEGRO_KEY_ESCAPE]) {
                mudar_cenario(game, "images/menu/menu.png");
                mudanca_estado(game, MENU);
            }
            break;

        case FASE4:
            if (key[ALLEGRO_KEY_ESCAPE]) {
                mudar_cenario(game, "images/menu/menu.png");
                mudanca_estado(game, MENU);
            }
            break;

        case NARRADOR:
            if (key[ALLEGRO_KEY_ESCAPE]) {
                mudar_cenario(game, "images/menu/menu.png");
                mudanca_estado(game, MENU);
            }
            break;
    }
}

void game_loop(Game* game) {
    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    game->iniciar = (Retangulo){ 420, 850, 309, 409 };
    game->opcoes = (Retangulo){ 420, 850, 432, 532 };
    game->como_jogar = (Retangulo){ 420, 850, 555, 655 };

    ALLEGRO_EVENT event;

    while (game->running) {
        al_wait_for_event(game->queue, &event);

        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
            check_input(game, key, event);

            switch (game->estado_game) {
                case MENU:
					break;

                case COMO_JOGAR:
                    break;

				case CONTEXTO:
                    break;

				case DIALOGO:
                    break;

                case FASE1: {
                    static double tempo_morte_cavaleiro = 0; // guarda quando o jogador morreu
                    static double tempo_morte_capanga = 0;
                    static int contador = 0;

                    atualizar_capanga(game->capanga, game->cavaleiro, 10);
                    atualizar_entidade(game->cavaleiro, game->boss->infos, game->capanga->infos, key, SCREEN_WIDTH, SCREEN_HEIGHT, 84, 10, 1.5, 0);

                    if (game->capanga->infos->hp <= 0) {
                        if (tempo_morte_capanga == 0) {
                            tempo_morte_capanga = al_get_time();
                        }

                         if (al_get_time() - tempo_morte_capanga >= 3.0) {
                            contador++;
                            reiniciar_entidade(game->capanga->infos);
                            game->capanga->infos->x = 1300;
                            game->capanga->estado = ESTADO_BUSCANDO;
                            tempo_morte_capanga = 0;
                        }
                    }
                    else {
                        // Se estiver vivo, zera o tempo de morte
                        tempo_morte_capanga = 0;
                    }

                    if (contador >= 3) {
                        printf("Avançando para o Ato 2...\n");
                        //game->ato = ATO2;
                        //mudanca_estado(game, FASE2);
                        //reiniciar_entidade(game->cavaleiro);
                        //reiniciar_entidade(game->boss->infos);
                        //tempo_morte_cavaleiro = 0; // reseta o contador
						mudanca_estado(game, NARRADOR);
                        reiniciar_entidade(game->cavaleiro);
                        reiniciar_entidade(game->boss->infos);
                        game->cavaleiro->x = SCREEN_WIDTH / 2 - 300;
						game->ato = ATO2;
                    }


                    if (game->cavaleiro->hp <= 0) {
                        if (tempo_morte_cavaleiro == 0) {
                            tempo_morte_cavaleiro = al_get_time(); // salva o tempo da morte
                        }

                        // Espera 5 segundos antes de trocar o estado
                        if (al_get_time() - tempo_morte_cavaleiro >= 5.0) {
                            printf("Avançando para o Ato 2...\n");
                            //game->ato = ATO2;
                            game->cavaleiro->x = SCREEN_WIDTH / 2 - 300;
                            reiniciar_entidade(game->cavaleiro);
                            reiniciar_entidade(game->capanga->infos);
                            game->capanga->infos->x = 800;
                            reiniciar_entidade(game->boss->infos);
                            contador = 0;
                            tempo_morte_cavaleiro = 0; // reseta o contador
                        }
                    }
                    else {
                        // Se estiver vivo, zera o tempo de morte
                        tempo_morte_cavaleiro = 0;
                    }

                    break;
                }
                   


                case FASE2: {
                    static double tempo_morte = 0; // guarda quando o jogador morreu
                    
                    atualizar_inimigo(game->boss, game->cavaleiro, 25, 590);
                    atualizar_entidade(game->cavaleiro, game->boss->infos, game->capanga->infos, key, SCREEN_WIDTH, SCREEN_HEIGHT, 84, 10, 1.5, 0);

                    /*if (game->cavaleiro->x > 1280) trocar_mapa(game, 1);
                    if (game->cavaleiro->x < -50) trocar_mapa(game, -1);*/

                    // Verifica morte
                    if (game->cavaleiro->hp <= 0) {
                        if (tempo_morte == 0) {
                            tempo_morte = al_get_time(); // salva o tempo da morte
                        }

                        // Espera 5 segundos antes de trocar o estado
                        if (al_get_time() - tempo_morte >= 5.0) {
                            game->ato = ATO3;
                            mudanca_estado(game, NARRADOR);
                            reiniciar_entidade(game->cavaleiro);
                            reiniciar_entidade(game->capanga->infos);
                            reiniciar_entidade(game->boss->infos);
                            game->cavaleiro->x = SCREEN_WIDTH / 2 - 300;
                            tempo_morte = 0; // reseta o contador
                        }
                    }
                    else {
                        // Se estiver vivo, zera o tempo de morte
                        tempo_morte = 0;
                    }

                    break;
                }

				case FASE3: {
                    static double tempo_morte = 0;

                    atualizar_entidade(game->patroclo, game->menelau->infos, game->capanga->infos, key, SCREEN_WIDTH, SCREEN_HEIGHT, 84, 10, 1.7, 0);
                    atualizar_inimigo(game->menelau, game->patroclo, 25, 550);
                    atualizar_capanga(game->capanga, game->patroclo, 10);

                    // Verifica morte
                    if (game->patroclo->hp <= 0) {
                        if (tempo_morte == 0) {
                            tempo_morte = al_get_time(); // salva o tempo da morte
                        }

                        // Espera 5 segundos antes de trocar o estado
                        if (al_get_time() - tempo_morte >= 5.0) {
                            game->ato = ATO4;
                            mudanca_estado(game, DIALOGO2);
                            reiniciar_entidade(game->cavaleiro);
                            reiniciar_entidade(game->capanga->infos);
                            reiniciar_entidade(game->menelau->infos);
                            game->cavaleiro->x = SCREEN_WIDTH / 2 - 300;
                            tempo_morte = 0; // reseta o contador
                        }
                    }
                    else {
                        // Se estiver vivo, zera o tempo de morte
                        tempo_morte = 0;
                    }

                    break;

                }

                case TRANSICAO:
                    reiniciar_entidade(game->cavaleiro);
                    atualizar_cavalo(game->cavalo, key, SCREEN_WIDTH, SCREEN_HEIGHT);
                    atualizar_entidade(game->cavaleiro, game->boss->infos, game->capanga->infos, key, SCREEN_WIDTH, SCREEN_HEIGHT, 84, 10, 1.5, 1);
                    if (game->cavaleiro->x > 1280 && game->cavalo->infos->x > 1280) {
                        mudar_cenario(game, "mapa__esparta.png");
                        mudanca_estado(game, FASE4);
                        game->cavaleiro->x = SCREEN_WIDTH / 2 - 300;
                    }
                    break;

                case NARRADOR:
                    break;


                case DIALOGO2:
                    break;


                case FASE4: {
                    static double tempo_morte2 = 0; // guarda quando o jogador morreu
                    static double tempo_morte1 = 0;

                    game->cavalo->infos->x = 150;
                    atualizar_inimigo(game->menelau, game->cavaleiro, 15, 550);
                    atualizar_entidade(game->cavaleiro, game->menelau->infos, game->capanga->infos, key, SCREEN_WIDTH, SCREEN_HEIGHT, 84, 15, 1.5, 0);
                    atualizar_hitbox(game->boss->infos);

                    /*if (game->cavaleiro->x > 1280) trocar_mapa(game, 1);
                    if (game->cavaleiro->x < -50) trocar_mapa(game, -1);*/

                    if (game->menelau->infos->hp <= 0) {
                        if (tempo_morte1 == 0) {
                            tempo_morte1 = al_get_time(); // salva o tempo da morte
                            printf("Boss morreu! Esperando 5 segundos...\n"); 
                        }
                        if (al_get_time() - tempo_morte1 >= 5.0) {
                            mudanca_estado(game, NARRADOR);
                            game->ato = ATO5;
                        }
                    }

                    if (game->cavaleiro->hp <= 0) {
                        if (tempo_morte2 == 0) {
                            tempo_morte2 = al_get_time(); // salva o tempo da morte
                        }

                        // Espera 5 segundos antes de trocar o estado
                        if (al_get_time() - tempo_morte2 >= 5.0) {
                            printf("Avançando para o Ato 2...\n");
                            //game->ato = ATO2;
                            game->cavaleiro->x = SCREEN_WIDTH / 2 - 300;
                            game->menelau->infos->x = 800;
                            reiniciar_entidade(game->cavaleiro);
                            reiniciar_entidade(game->menelau->infos);
                            tempo_morte2 = 0; // reseta o contador
                        }
                    }


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
                            mudanca_estado(game, FASE1);
                        }
                        break;
                    case ATO2:
                        game->etapa_ato2++;
                        if (game->etapa_ato2 == NEXT_ATO2) {
                            mudar_cenario(game, "mapa_acampamento.png");
                            mudanca_estado(game, NARRADOR);
                        }
                    }
                }
            }

            if (game->estado_game == DIALOGO2) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    switch (game->ato) {
                    case ATO4:
                        game->etapa_ato4++;
                        if (game->etapa_ato4 == NEXT_ATO4) {
                            mudar_cenario(game, "cidade_troia.png");
							mudanca_estado(game, TRANSICAO);
                        }
                        break;
                    }
                }
            }

            if (game->estado_game == DIALOGO3) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    switch (game->ato) {
                    case ATO6:
                        game->etapa_ato6++;
                        if (game->etapa_ato6 == NEXT_ATO6) {
                            desenhar_dialogo_final(game);
							mudanca_estado(game, FINAL);
                        }
                        break;
                    }
                }
            }

            if (game->estado_game == NARRADOR) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    switch (game->ato) {
                    case ATO2:
                        game->etapa_ato2++;
                        if (game->etapa_ato2 == NEXT_ATO2) {
                            mudar_cenario(game, "mapa_acampamento.png");
                            mudanca_estado(game, FASE2);
                        }
                        break;
                    case ATO3:
                        game->etapa_ato3++;
                        if (game->etapa_ato3 == NEXT_ATO3) {
                            mudar_cenario(game, "mapa_porto.png");
                            mudanca_estado(game, FASE3);
                        }
                        break;
                    case ATO5:
                        game->etapa_ato5++;
                        if (game->etapa_ato5 == NEXT_ATO5) {
                            mudanca_estado(game, DIALOGO3);
							game->ato = ATO6;
                        }
                        break;
                    }
                }
            }

            if (game->estado_game == CONTEXTO) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    switch (game->ato) {
                    case ATO0:
                        game->etapa_ato0++;
                        if (game->etapa_ato0 == NEXT_ATO3) {
                            game->ato = ATO1;
                            mudanca_estado(game, DIALOGO);
                        }
                        break;
                    }
                }
            }

            if (game->estado_game == TRANSICAO) {
                if (game->cavaleiro->x > 1280 && game->cavalo->infos->x > 1280) {
                    mudar_cenario(game, "cidade__esparta.png");
                    game->cavaleiro->x = 200;
                    game->cavalo->infos->x = 150;

                }
            }
            
            // ESC fecha o jogo no menu
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE && game->estado_game == MENU) {
                game->running = false;
            }
            
            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && game->estado_game == MENU) {
                mudanca_estado(game, CONTEXTO);
				game->ato = ATO0;
            }

            // ESC no jogo ? volta ao menu
            else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE && game->estado_game == FASE2) {
                mudar_cenario(game, "images/menu/menu.png");
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
            game->mouse_x = event.mouse.x;

            game->mouse_y = event.mouse.y;
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if (area_clicavel(game->mouse_x, game->mouse_y, game->iniciar) && game->estado_game == MENU) {
                mudanca_estado(game, CONTEXTO);
                game->ato = ATO0;
            }
            else if (area_clicavel(game->mouse_x, game->mouse_y, game->como_jogar) && game->estado_game == MENU) {
                mudar_cenario(game, "imagem_menu.png");
                mudanca_estado(game, COMO_JOGAR);
            }
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
                    desenhar_menu(game, SCREEN_WIDTH, SCREEN_HEIGHT, "images/menu/menu.png");
                    break;

                case COMO_JOGAR:
                    desenhar_menu(game, SCREEN_WIDTH, SCREEN_HEIGHT, "images/menu/como_jogar.png");
                    break;

                case CONTEXTO:
					desenhar_narrador(game, SCREEN_WIDTH, SCREEN_HEIGHT);
					game->ato = ATO0;
					break;

                case NARRADOR:
                    desenhar_narrador(game, SCREEN_WIDTH, SCREEN_HEIGHT);
                    break;

                case DIALOGO:
                    desenhar_dialogo(game);
				    break;

                case FASE1:
                    desenhar_cenario(game->cenario, SCREEN_WIDTH, SCREEN_HEIGHT);
                    desenhar_capanga(game->capanga->infos, 2.0, 1);
                    desenhar_entidade(game->cavaleiro, 2.0);
                    desenhar_hp_fixa(game->cavaleiro, 20, 20, false);
                    desenhar_hp_fixa(game->capanga->infos, SCREEN_WIDTH - 400 - 20, 20, true);
                    break;
    
                case FASE2:
                    desenhar_cenario(game->cenario, SCREEN_WIDTH, SCREEN_HEIGHT);
                    desenhar_inimigo(game->boss, 2.5);
                    desenhar_entidade(game->cavaleiro, 2.0);//cavaleiro
                    desenhar_hp_fixa(game->cavaleiro, 20, 20, false);
                    desenhar_hp_fixa(game->boss->infos, SCREEN_WIDTH - 400 - 20, 20, true);
					break;

                case FASE3:
                    desenhar_cenario(game->cenario, SCREEN_WIDTH, SCREEN_HEIGHT);
                    desenhar_inimigo(game->menelau, 2.5);
                    desenhar_capanga(game->capanga->infos, 2.0, 3);
                    desenhar_entidade(game->patroclo, 1.7);//cavaleiro
                    desenhar_hp_fixa(game->patroclo, 20, 20, false);
                    desenhar_hp_fixa(game->menelau->infos, SCREEN_WIDTH - 400 - 20, 20, true);
                    
                    break;

                case TRANSICAO:
                    //mudar_cenario(game, "cidade_troia.png");
                    desenhar_cenario(game->cenario, SCREEN_WIDTH, SCREEN_HEIGHT);
                    desenhar_cavalo(game->cavalo, 1);
                    desenhar_entidade(game->cavaleiro, 2.0);
                    break;

                case DIALOGO2:
                    game->ato = ATO4;
                    desenhar_dialogo_ulisses(game);
                    break;

                case FASE4:
                    desenhar_cenario(game->cenario, SCREEN_WIDTH, SCREEN_HEIGHT);
                    desenhar_cavalo(game->cavalo, 1);
                    desenhar_inimigo(game->menelau, 2.5);
                    desenhar_entidade(game->cavaleiro, 2.0);
                    desenhar_hp_fixa(game->cavaleiro, 20, 20, false);
                    desenhar_hp_fixa(game->menelau->infos, SCREEN_WIDTH - 400 - 20, 20, true);
                    break;

                case DIALOGO3:
					game->ato = ATO6;
                    desenhar_dialogo_final(game);
                    break;

                case FINAL:
					desenhar_final(game, SCREEN_WIDTH, SCREEN_HEIGHT);
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
    destruir_inimigo(game->capanga);
}

void destruir_sprite(Sprite* sprite) {
    if (sprite) {
        for (int i = 0; i < sprite->num_frames; i++) {
            if (sprite->frames[i]) {
                al_destroy_bitmap(sprite->frames[i]);
            }
        }
        free(sprite->frames);
        if (sprite->sheet) {
            al_destroy_bitmap(sprite->sheet);
        }
        free(sprite);
    }
}

void trocar_mapa(Game* game, int direcao) {
    const char* mapas[] = {
        "mapa_grecia.png",
        "mapa__esparta.png",
        "mapa_acampamento.png",
        "mapa_porto.png",
        "mapa_castelo.png"
        "cidade_troia.png"
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