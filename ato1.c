#include "ato1.h"
#include "ui.h"
#include <allegro5/allegro.h>

static int etapa = 0;

bool iniciar_ato1(ALLEGRO_FONT* fonte, ALLEGRO_BITMAP* pergaminho) {
    al_clear_to_color(al_map_rgb(0, 0, 0));

    switch (etapa) {
    case 0:
        desenhar_caixa_dialogo(pergaminho, fonte, "Ato I - O Despertar dos Mortais...");
        break;
    case 1:
        desenhar_caixa_dialogo(pergaminho, fonte, "Os ventos trazem rumores de guerra...");
        break;
    case 2:
        desenhar_caixa_dialogo(pergaminho, fonte, "Homens e deuses se preparam para o inevitável.");
        break;
    case 3:
        return true; // sinaliza que o diálogo terminou
    }

    al_flip_display(); // mostra o texto
    etapa++;
    return false;
}

