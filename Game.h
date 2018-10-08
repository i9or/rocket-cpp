//
// Created by Igor Pelekhan on 02/10/2018.
//

#ifndef GAME_CPP_GAME_H
#define GAME_CPP_GAME_H

#include <SDL.h>

class Game {
public:
    Game();

    bool Initialize();

    void RunLoop();

    void ShutDown();

private:
    void ProcessInput();

    void UpdateGame();

    void GenerateOutput();

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;

    bool mIsRunning;

    const int mWidth = 1024;
    const int mHeight = 768;
};


#endif //GAME_CPP_GAME_H
