//
// Created by Igor Pelekhan on 02/10/2018.
//

#include "Game.h"

Game::Game() :
        mWindow(nullptr),
        mIsRunning(true),
        mTicksCount(0),
        mPaddleDirection(0) {

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

    mPaddlePosition.x = mThickness + mThickness / 2.0f;
    mPaddlePosition.y = mHeight / 2.0f;
    mBallPosition.x = mWidth / 2.0f;
    mBallPosition.y = mHeight / 2.0f;
    mBallVelocity.x = -200.0f;
    mBallVelocity.y = 235.0f;

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

    mPaddleDirection = 0;

    if (state[SDL_SCANCODE_W]) {
        mPaddleDirection -= 1;
    }

    if (state[SDL_SCANCODE_S]) {
        mPaddleDirection += 1;
    }
}

void Game::UpdateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    mTicksCount = SDL_GetTicks();

    if (mPaddleDirection != 0) {
        mPaddlePosition.y += mPaddleDirection * 300.0f * deltaTime;

        if (mPaddlePosition.y < (mPaddleHeight / 2.0f + mThickness)) {
            mPaddlePosition.y = mPaddleHeight / 2.0f + mThickness;
        }

        if (mPaddlePosition.y > (mHeight - mPaddleHeight / 2.0f - mThickness)) {
            mPaddlePosition.y = mHeight - mPaddleHeight / 2.0f - mThickness;
        }
    }

    mBallPosition.x += mBallVelocity.x * deltaTime;
    mBallPosition.y += mBallVelocity.y * deltaTime;

    float diff = mPaddlePosition.y - mBallPosition.y;
    diff = (diff > 0.0f) ? diff : -diff;

    if (diff <= mPaddleHeight / 2.0f &&
        mBallPosition.x <= (mPaddlePosition.x + mThickness / 2.0f) &&
        mBallPosition.x >= (mPaddlePosition.x - mThickness / 2.0f) &&
        mBallVelocity.x < 0.0f) {
        mBallVelocity.x *= -1.0;
    } else if (mBallPosition.x <= 0.0f) {
        mIsRunning = false;
    }

    if (mBallPosition.x >= (mWidth - mThickness) && mBallVelocity.x > 0.0f) {
        mBallVelocity.x *= -1.0f;
    }

    if (mBallPosition.y <= mThickness && mBallVelocity.y < 0.0f) {
        mBallVelocity.y *= -1;
    }

    if (mBallPosition.y >= (mHeight - mThickness) &&
        mBallVelocity.y > 0.0f) {
        mBallVelocity.y *= -1;
    }
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(mRenderer, 41, 128, 185, 255);
    SDL_RenderClear(mRenderer);

    // Drawing walls
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    SDL_Rect wall{0, 0, mWidth, mThickness};
    SDL_RenderFillRect(mRenderer, &wall);

    wall.y = mHeight - mThickness;
    SDL_RenderFillRect(mRenderer, &wall);

    wall.x = mWidth - mThickness;
    wall.y = 0;
    wall.w = mThickness;
    wall.h = mWidth;
    SDL_RenderFillRect(mRenderer, &wall);

    // Drawing ball
    SDL_Rect ball{
            static_cast<int>(mBallPosition.x - mThickness / 2.f),
            static_cast<int>(mBallPosition.y - mThickness / 2.f),
            mThickness,
            mThickness
    };
    SDL_RenderFillRect(mRenderer, &ball);

    // Drawing paddle
    SDL_Rect paddle{
            static_cast<int>(mPaddlePosition.x - mThickness / 2.f),
            static_cast<int>(mPaddlePosition.y - mPaddleHeight / 2.f),
            mThickness,
            mPaddleHeight
    };
    SDL_RenderFillRect(mRenderer, &paddle);

    SDL_RenderPresent(mRenderer);
}


