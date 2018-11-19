#include "Ship.h"
#include "AnimatedSpriteComponent.h"
#include "Game.h"

Ship::Ship(Game* game)
    : Actor(game)
    , mHorizontalSpeed(0.0f)
    , mVerticalSpeed(0.0f) {
    AnimatedSpriteComponent* animatedSpriteComponent = new AnimatedSpriteComponent(this);
    std::vector<SDL_Texture*> animationTextures = {
        game->GetTexture("assets/rocket1.png"),
        game->GetTexture("assets/rocket2.png"),
        game->GetTexture("assets/rocket3.png")
    };

    animatedSpriteComponent->SetAnimationTextures(animationTextures);
}

void Ship::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);

    Vector2 pos = GetPosition();
    pos.x += mHorizontalSpeed * deltaTime;
    pos.y += mVerticalSpeed * deltaTime;

    float scale = GetScale();

    if (pos.x < 262.0f * scale) {
        pos.x = 262.0f * scale;
    } else if (pos.x > 1280.0f - 262.0f * scale) {
        pos.x = 1280.0f - 262.0f * scale;
    }

    if (pos.y < 150.0f * scale) {
        pos.y = 150.0f * scale;
    } else if (pos.y > 720.0f - 150.0f * scale) {
        pos.y = 720.0f - 150.0f * scale;
    }

    SetPosition(pos);
}

void Ship::ProcessKeyboard(const std::uint8_t* state) {
    mHorizontalSpeed = 0.0f;
    mVerticalSpeed = 0.0f;

    if (state[SDL_SCANCODE_D]) {
        mHorizontalSpeed += 250.0f;
    }

    if (state[SDL_SCANCODE_A]) {
        mHorizontalSpeed -= 250.0f;
    }

    if (state[SDL_SCANCODE_S]) {
        mVerticalSpeed += 300.0f;
    }

    if (state[SDL_SCANCODE_W]) {
        mVerticalSpeed -= 300.0f;
    }
}
