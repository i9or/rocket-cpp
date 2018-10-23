#include "Game.h"

int main() {
    Game game;

    bool success = game.Initialize();
    if (success) {
        game.RunLoop();
    }

    game.ShutDown();

    return 0;
}
