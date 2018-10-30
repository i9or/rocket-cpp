#ifndef GAME_CPP_GAME_H
#define GAME_CPP_GAME_H

#include "SDL.h"

#include <random>
#include <string>
#include <vector>

struct Vector2 {
    float x;
    float y;
};

struct Ball {
    Vector2 position;
    Vector2 velocity;
    bool shouldBeRendered;
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

    void UpdatePaddle(const float& deltaTime, Vector2& paddlePosition, int& paddleDirection);

    void UpdateBalls(const float& deltaTime);

    void GenerateOutput();

    float mLastMeasurement;

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Uint32 mTicksCount;
    bool mIsRunning;

    static const int mWidth = 800;
    static const int mHeight = 600;
    static const int mThickness = 10;
    static constexpr int mPaddleHeight = mThickness * 6;

    int mPaddleDirectionA;
    Vector2 mPaddlePositionA;
    int mPaddleDirectionB;
    Vector2 mPaddlePositionB;

    static const int mBallsNumber = 5;
    std::vector<Ball> mBalls;
};

#endif // GAME_CPP_GAME_H
