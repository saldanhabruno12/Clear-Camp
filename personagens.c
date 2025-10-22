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
    .colunas = {8, 8, 5, 6, 12, 7},
    .linhas = {1, 1, 1, 1, 1, 1},
    .frames = { 8, 8, 5, 6, 12, 7 }
};

DadosAnimacoes boss = {
    .caminhos = {
        [ANDANDO] = "images/boss/corrida.png",
        [CORRENDO] = "images/boss/corrida.png",
        [PULANDO] = "images/boss/pulo.png",
        [ATACANDO] = "images/boss/ataque.png",
        [MORRENDO] = "images/boss/morte.png",
        [PARADO] = "images/boss/parado.png"
},
    .colunas = {2, 2, 2, 8, 2, 2},
    .linhas = {4, 4, 4, 1, 2, 4},
    .frames = {8, 8, 8, 8, 4, 8}
};