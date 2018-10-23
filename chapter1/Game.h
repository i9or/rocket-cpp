#ifndef GAME_CPP_GAME_H
#define GAME_CPP_GAME_H

#include "SDL.h"

struct Vector2 {
    float x;
    float y;
};

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

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Uint32 mTicksCount;
    bool mIsRunning;

    static const int mWidth = 1024;
    static const int mHeight = 768;
    static const int mThickness = 15;
    static constexpr int mPaddleHeight = mThickness * 6;

    int mPaddleDirection;
    Vector2 mPaddlePosition;
    Vector2 mBallPosition;
    Vector2 mBallVelocity;
};

#endif // GAME_CPP_GAME_H
