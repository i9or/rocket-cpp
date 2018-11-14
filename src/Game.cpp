#include "Game.h"
#include "SDL_image.h"

#include <algorithm>

#include "Actor.h"
#include "BackgroundSpriteComponent.h"
#include "Ship.h"
#include "SpriteComponent.h"

Game::Game()
    : mWindow(nullptr)
    , mRenderer(nullptr)
    , mIsRunning(true)
    , mUpdatingActors(false) {
}

bool Game::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Rocket Adventures", 100, 100, mScreenWidth, mScreenHeight, 0);
    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Log("Unable to intialize SDL_Image: %s", SDL_GetError());
        return false;
    }

    LoadData();

    mTicksCount = SDL_GetTicks();

    return true;
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown() {
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::ProcessInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }

    mShip->ProcessKeyboard(state);
}

void Game::UpdateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();

    mUpdatingActors = true;
    for (auto actor : mActors) {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;

    for (auto pending : mPendingActors) {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    std::vector<Actor*> deadActors;
    for (auto actor : mActors) {
        if (actor->GetState() == Actor::EDead) {
            deadActors.emplace_back(actor);
        }
    }

    for (auto actor : deadActors) {
        delete actor;
    }
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    for (auto sprite : mSprites) {
        sprite->Draw(mRenderer);
    }

    SDL_RenderPresent(mRenderer);
}

void Game::LoadData() {
    mShip = new Ship(this);
    mShip->SetPosition(Vector2(150.0f, mScreenHeight / 2.0f));
    mShip->SetScale(0.5f);

    Actor* temp = new Actor(this);
    temp->SetPosition(Vector2(mScreenWidth / 2.0f, mScreenHeight / 2.0f));

    BackgroundSpriteComponent* bg = new BackgroundSpriteComponent(temp);
    bg->SetScreenSize(Vector2(mScreenWidth, mScreenHeight));
    std::vector<SDL_Texture*> texs = {
        GetTexture("assets/background1.png"),
        GetTexture("assets/background2.png")
    };

    bg->SetBackgroundTextures(texs);
    bg->SetScrollSpeed(-100.0f);

    bg = new BackgroundSpriteComponent(temp, 50);
    bg->SetScreenSize(Vector2(mScreenWidth, mScreenHeight));
    texs = {
        GetTexture("assets/stars1.png"),
        GetTexture("assets/stars1.png")
    };
    bg->SetBackgroundTextures(texs);
    bg->SetScrollSpeed(-200.0f);
}

void Game::UnloadData() {
    while (!mActors.empty()) {
        delete mActors.back();
    }

    for (auto t : mTextures) {
        SDL_DestroyTexture(t.second);
    }

    mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName) {
    SDL_Texture* texture = nullptr;

    auto iter = mTextures.find(fileName);
    if (iter != mTextures.end()) {
        texture = iter->second;
    } else {
        SDL_Surface* surface = IMG_Load(fileName.c_str());
        if (!surface) {
            SDL_Log("Failed to load texture file %s", fileName.c_str());
            return nullptr;
        }

        texture = SDL_CreateTextureFromSurface(mRenderer, surface);
        SDL_FreeSurface(surface);
        if (!texture) {
            SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
            return nullptr;
        }

        mTextures.emplace(fileName.c_str(), texture);
    }

    return texture;
}

void Game::AddActor(Actor* actor) {
    if (mUpdatingActors) {
        mPendingActors.emplace_back(actor);
    } else {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor) {
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end()) {
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end()) {
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::AddSprite(SpriteComponent* sprite) {
    int drawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); ++iter) {
        if (drawOrder < (*iter)->GetDrawOrder()) {
            break;
        }
    }

    mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite) {
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}
