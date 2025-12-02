#include "game.h"

int main() {
    Game game;

    if (!game_init(&game)) {
        return -1; // falha na inicialização
    }

    game_loop(&game);
    game_shutdown(&game);

    return 0;
}
