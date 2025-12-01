#include "personagens.h"

DadosAnimacoes cavalo = {
    .caminhos = {
    [ANDANDO] = "images/cavalo/cavalo(prop).png",
    [CORRENDO] = "images/cavalo/cavalo(prop).png",
    [PULANDO] = "images/cavalo/cavalo(prop).png",
    [ATACANDO] = "images/cavalo/cavalo(prop).png",
    [MORRENDO] = "images/cavalo/cavalo(prop).png",
    [PARADO] = "images/cavalo/cavalo(prop).png"
},
    .colunas = {1, 1, 1, 1, 1, 1},
    .linhas = {1, 1, 1, 1, 1, 1},
    .frames = {1, 1, 1, 1, 1, 1}
};

DadosAnimacoes cavaleiro = {
    .caminhos = {
    [ANDANDO] = "images/cavaleiro/caminhar.png",
    [CORRENDO] = "images/cavaleiro/corrida.png",
    [PULANDO] = "images/cavaleiro/pulo.png",
    [ATACANDO] = "images/cavaleiro/ataque1.png",
    [MORRENDO] = "images/cavaleiro/morte.png",
    [PARADO] = "images/cavaleiro/parado.png",
    [MORTO] = "images/cavaleiro/morto.png"
},
    .colunas = {8, 8, 5, 6, 12, 7, 1},
    .linhas = {1, 1, 1, 1, 1, 1, 1},
    .frames = {8, 8, 5, 6, 12, 7, 1}
};

DadosHitbox cavaleiro_hitbox = {
    .largura_sprite = 64,
    .altura_sprite = 64,
    .hitbox_offset_x = 40,
    .hitbox_offset_y = 40,
    .hitbox_largura = 44,
    .hitbox_altura = 59
};

DadosAnimacoes patroclo = {
    .caminhos = {
        [ANDANDO] = "images/patroclo/corrida.png",
        [CORRENDO] = "images/patroclo/corrida.png",
        [PULANDO] = "images/patroclo/pulo.png",
        [ATACANDO] = "images/patroclo/ataque.png",
        [MORRENDO] = "images/patroclo/morte.png",
        [PARADO] = "images/patroclo/parado.png",
        [MORTO] = "images/patroclo/morte.png"
},
    .colunas = {6, 6, 2, 4, 9, 10, 1},
    .linhas = {1, 1, 1, 1, 1, 1, 1},
    .frames = {6, 6, 2, 4, 9, 10, 1}
};

DadosHitbox patroclo_hitbox = {
    .largura_sprite = 135,
    .altura_sprite = 135,
    .hitbox_offset_x = 111,
    .hitbox_offset_y = 111,
    .hitbox_largura = 115,
    .hitbox_altura = 130
};

DadosAnimacoes menelau = {
    .caminhos = {
        [ANDANDO] = "images/menelau/corrida.png",
        [CORRENDO] = "images/menelau/corrida.png",
        [PULANDO] = "images/menelau/pulo.png",
        [ATACANDO] = "images/menelau/ataque.png",
        [MORRENDO] = "images/menelau/morte.png",
        [PARADO] = "images/menelau/parado.png",
        [MORTO] = "images/menelau/morte.png"
},
    .colunas = {8, 8, 4, 6, 9, 11, 1},
    .linhas = {1, 1, 1, 1, 1, 1, 1},
    .frames = {8, 8, 4, 6, 9, 11, 1}
};

DadosHitbox menelau_hitbox = {
    .largura_sprite = 140,
    .altura_sprite = 140,
    .hitbox_offset_x = 116,
    .hitbox_offset_y = 116,
    .hitbox_largura = 121,
    .hitbox_altura = 135
};


DadosAnimacoes capanga = {
    .caminhos = {
    [ANDANDO] = "images/capanga/andando.png",
    [CORRENDO] = "images/capanga/andando.png",
    [PULANDO] = "images/capanga/andando.png",
    [ATACANDO] = "images/capanga/ataque.png",
    [MORRENDO] = "images/capanga/morte.png",
    [PARADO] = "images/capanga/respirando.png",
    [MORTO] = "images/capanga/morte.png"
},
    .colunas = {8, 8, 8, 10, 9, 4, 9},
    .linhas = {1, 1, 1, 1, 1, 1, 1},
    .frames = {8, 8, 8, 10, 9, 4, 9}
};

DadosHitbox capanga_hitbox = {
    .largura_sprite = 42,
    .altura_sprite = 42,
    .hitbox_offset_x = 18,
    .hitbox_offset_y = 18,
    .hitbox_largura = 22,
    .hitbox_altura = 37
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

DadosHitbox boss_hitbox = {
    .largura_sprite = 128,
    .altura_sprite = 128,
    .hitbox_offset_x = 20,
    .hitbox_offset_y = 10,
    .hitbox_largura = 88,
    .hitbox_altura = 110
};