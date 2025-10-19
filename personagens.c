#include "entidade.h"

DadosAnimacoes cavaleiro = {
    .caminhos = {
    [ANDANDO] = "images/cavaleiro/caminhar.png",
    [CORRENDO] = "images/cavaleiro/corrida.png",
    [PULANDO] = "images/cavaleiro/pulo.png",
    [ATACANDO] = "images/cavaleiro/ataque1.png",
    [MORRENDO] = "images/cavaleiro/morte.png",
    [PARADO] = "images/cavaleiro/parado.png"
},
    .frames = { 8, 8, 5, 6, 12, 7 }
};