#include "cenario.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>



ALLEGRO_BITMAP* carregar_cenario(const char* caminho) {
    ALLEGRO_BITMAP* mapa = al_load_bitmap(caminho);
    if (!mapa) {
        printf("Erro ao carregar cenario: %s\n", caminho);
        return NULL;
    }
    return mapa;
}

void desenhar_cenario(ALLEGRO_BITMAP* mapa, int tela_largura, int tela_altura) {
    if (!mapa) return;

    int img_largura = al_get_bitmap_width(mapa);
    int img_altura = al_get_bitmap_height(mapa);

    // força a imagem a ocupar 100% da tela
    al_draw_scaled_bitmap(
        mapa,
        0, 0, img_largura, img_altura,
        0, 0, tela_largura, tela_altura,
        0
    );
}

void destruir_cenario(ALLEGRO_BITMAP* mapa) {
    if (mapa) al_destroy_bitmap(mapa);
}
