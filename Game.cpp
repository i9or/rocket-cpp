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
            mWidth, mHeight,
            0
    );

    if (!mWindow) {
        SDL_Log("Failed to create a window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(
            mWindow,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!mRenderer) {
        SDL_Log("Failed to created a renderer: %s", SDL_GetError());
        return false;
    }

    // FIXME: macOS Mojave black screen workaround
    SDL_PumpEvents();
    SDL_SetWindowSize(mWindow, mWidth, mHeight);
    // -------------------------------------------

    return true;
}

void Game::ShutDown() {
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
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

    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }
}

void Game::UpdateGame() {

}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(mRenderer, 41, 128, 185, 255);
    SDL_RenderClear(mRenderer);
    SDL_RenderPresent(mRenderer);
}


