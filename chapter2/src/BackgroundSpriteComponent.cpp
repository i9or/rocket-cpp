#include "BackgroundSpriteComponent.h"
#include "Actor.h"

BackgroundSpriteComponent::BackgroundSpriteComponent(Actor* owner, int drawOrder)
    : SpriteComponent(owner, drawOrder)
    , mScrollSpeed(0.0f)
{
}

void BackgroundSpriteComponent::Update(float deltaTime)
{
    SpriteComponent::Update(deltaTime);

    for (auto& bg : mBackgroundTextures) {
        bg.mOffset.x += mScrollSpeed * deltaTime;

        if (bg.mOffset.x < -mScreenSize.x) {
            bg.mOffset.x = (mBackgroundTextures.size() - 1) * mScreenSize.x - 1;
        }
    }
}
