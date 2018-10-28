//
// Created by Igor Pelekhan on 02/10/2018.
//

#include "Game.h"

Game::Game()
    : mWindow(nullptr)
    , mTicksCount(0)
    , mIsRunning(true)
    , mPaddleDirectionA(0)
    , mPaddleDirectionB(0) {
}

bool Game::Initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Chapter 1 | Pong", 100, 100, mWidth, mHeight, 0);

    if (!mWindow) {
        SDL_Log("Failed to create a window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!mRenderer) {
        SDL_Log("Failed to created a renderer: %s", SDL_GetError());
        return false;
    }

    mPaddlePositionA.x = mThickness + mThickness / 2.0f;
    mPaddlePositionA.y = mHeight / 2.0f;

    mPaddlePositionB.x = mWidth - mThickness - mThickness / 2.0f;
    mPaddlePositionB.y = mHeight / 2.0f;

    std::random_device rd;
    std::mt19937 mt(rd());
    int boundry = mThickness * 2;
    std::uniform_int_distribution<int> verticalPositionDistribution(boundry, mHeight - boundry);
    std::uniform_int_distribution<int> velocityValueDistribution(80, 235);
    std::uniform_int_distribution<int> velocityDirectionDistibution(0, 1);
    int table[]{-1, 1};

    for (int i = 0; i < mBallsNumber; ++i) {
        Ball newBall;

        newBall.position.x = mWidth / 2.0f;
        newBall.position.y = verticalPositionDistribution(mt);
        newBall.velocity.x = velocityValueDistribution(mt) * table[velocityDirectionDistibution(mt)];
        newBall.velocity.y = velocityValueDistribution(mt) * table[velocityDirectionDistibution(mt)];
        newBall.shouldBeRendered = true;

        mBalls.push_back(newBall);
    }

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

    const Uint8* state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }

    // Process first player paddle movement
    mPaddleDirectionA = 0;

    if (state[SDL_SCANCODE_W]) {
        mPaddleDirectionA -= 1;
    }

    if (state[SDL_SCANCODE_S]) {
        mPaddleDirectionA += 1;
    }

    // Process second player paddle movement
    mPaddleDirectionB = 0;

    if (state[SDL_SCANCODE_I]) {
        mPaddleDirectionB -= 1;
    }

    if (state[SDL_SCANCODE_K]) {
        mPaddleDirectionB += 1;
    }
}

void Game::UpdateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    mTicksCount = SDL_GetTicks();

    UpdatePaddle(deltaTime, mPaddlePositionA, mPaddleDirectionA);
    UpdatePaddle(deltaTime, mPaddlePositionB, mPaddleDirectionB);

    UpdateBalls(deltaTime);
}

void Game::UpdatePaddle(const float& deltaTime, Vector2& paddlePosition, int& paddleDirection) {
    if (paddleDirection != 0) {
        paddlePosition.y += paddleDirection * 300.0f * deltaTime;

        if (paddlePosition.y < (mPaddleHeight / 2.0f + mThickness)) {
            paddlePosition.y = mPaddleHeight / 2.0f + mThickness;
        }

        if (paddlePosition.y > (mHeight - mPaddleHeight / 2.0f - mThickness)) {
            paddlePosition.y = mHeight - mPaddleHeight / 2.0f - mThickness;
        }
    }
}

void Game::UpdateBalls(const float& deltaTime) {
    for (auto& ball : mBalls) {
        if (ball.shouldBeRendered) {
            ball.position.x += ball.velocity.x * deltaTime;
            ball.position.y += ball.velocity.y * deltaTime;

            float diffA = mPaddlePositionA.y - ball.position.y;
            diffA = (diffA > 0.0f) ? diffA : -diffA;

            float diffB = mPaddlePositionB.y - ball.position.y;
            diffB = (diffB > 0.0f) ? diffB : -diffB;

            if (diffA <= mPaddleHeight / 2.0f &&                                   //
                    ball.position.x <= (mPaddlePositionA.x + mThickness / 2.0f) && //
                    ball.position.x >= (mPaddlePositionA.x - mThickness / 2.0f) && //
                    ball.velocity.x < 0.0f) {
                ball.velocity.x *= -1.0;
            } else if (diffB <= mPaddleHeight / 2.0f &&                            //
                    ball.position.x <= (mPaddlePositionB.x + mThickness / 2.0f) && //
                    ball.position.x >= (mPaddlePositionB.x - mThickness / 2.0f) && //
                    ball.velocity.x > 0.0f) {
                ball.velocity.x *= -1.0;
            } else if (ball.position.x <= 0.0f || ball.position.x >= mWidth) {
                ball.shouldBeRendered = false;
            }

            // Collisions with top and bottom walls
            if (ball.position.y <= mThickness && ball.velocity.y < 0.0f) {
                ball.velocity.y *= -1;
            }

            if (ball.position.y >= (mHeight - mThickness) && ball.velocity.y > 0.0f) {
                ball.velocity.y *= -1;
            }
        }
    }
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    // Drawing walls
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    SDL_Rect wall {0, 0, mWidth, mThickness};
    SDL_RenderFillRect(mRenderer, &wall);

    wall.y = mHeight - mThickness;
    SDL_RenderFillRect(mRenderer, &wall);

    // Drawing balls
    for (auto ball : mBalls) {
        if (ball.shouldBeRendered) {
            SDL_Rect ballRect {static_cast<int>(ball.position.x - mThickness / 2.0f),
                    static_cast<int>(ball.position.y - mThickness / 2.0f), mThickness, mThickness};
            SDL_RenderFillRect(mRenderer, &ballRect);
        }
    }

    // Drawing paddle A
    SDL_Rect paddleA {static_cast<int>(mPaddlePositionA.x - mThickness / 2.0f),
            static_cast<int>(mPaddlePositionA.y - mPaddleHeight / 2.0f), mThickness, mPaddleHeight};
    SDL_RenderFillRect(mRenderer, &paddleA);

    // Drawing paddle B
    SDL_Rect paddleB {static_cast<int>(mPaddlePositionB.x - mThickness / 2.0f),
            static_cast<int>(mPaddlePositionB.y - mPaddleHeight / 2.0f), mThickness, mPaddleHeight};
    SDL_RenderFillRect(mRenderer, &paddleB);

    SDL_RenderPresent(mRenderer);
}
