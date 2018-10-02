//
// Created by Igor Pelekhan on 02/10/2018.
//

#include "Game.h"

Game::Game() :
        mWindow(nullptr),
        mIsRunning(true) {

}

bool Game::Initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
            "Game Programming in C++",
            100, 100,
            1024, 768,
            0
    );

    if (!mWindow) {
        SDL_Log("Failed to create a window: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Game::ShutDown() {
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            default:
                break;
        }
    }
}

void Game::UpdateGame() {

}

void Game::GenerateOutput() {

}


