#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

int main() {

    if (!al_init()) {
        printf("Erro ao inicializar Allegro\n");
        return -1;
    }

    if (!al_init_image_addon()) {
        printf("Erro ao inicializar addon de imagens\n");
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
    al_register_event_source(fila, al_get_display_event_source(display));


    ALLEGRO_BITMAP* fundo = al_load_bitmap("mapa_grecia.png");
    if (!fundo) {
        printf("Erro ao carregar imagem! Verifique se 'mapa_grecia.png' está na mesma pasta do executável.\n");
        system("pause"); // pausa para você ver a mensagem antes de fechar
        al_destroy_event_queue(fila);
        al_destroy_display(display);
        return -1;
    }
    // Tamanho original da imagem
    int img_largura = al_get_bitmap_width(fundo);
    int img_altura = al_get_bitmap_height(fundo);

    // Calcular escala mantendo proporção
    float escala_x = (float)tela_largura / img_largura;
    float escala_y = (float)tela_altura / img_altura;
    float escala_final = (escala_x < escala_y) ? escala_x : escala_y;

    // Dimensões finais da imagem redimensionada
    int nova_largura = img_largura * escala_final;
    int nova_altura = img_altura * escala_final;


    int pos_x = (tela_largura - nova_largura) / 2;
    int pos_y = (tela_altura - nova_altura) / 2;


    bool rodando = true;
    while (rodando) {

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
    }

    al_destroy_bitmap(fundo);
    al_destroy_event_queue(fila);
    al_destroy_display(display);

    return 0;
}