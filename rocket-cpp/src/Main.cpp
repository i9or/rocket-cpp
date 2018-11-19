#define SDL_MAIN_HANDLED
#include "Game.h"

int main() {
    Game game;
    bool success = game.Initialize();

    if (success) {
        game.RunLoop();
    }

    game.Shutdown();
    return 0;
}
