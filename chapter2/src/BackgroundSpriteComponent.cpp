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

void BackgroundSpriteComponent::Draw(SDL_Renderer* renderer)
{
    for (auto& bg : mBackgroundTextures) {
        SDL_Rect r;

        r.w = static_cast<int>(mScreenSize.x);
        r.h = static_cast<int>(mScreenSize.y);
        r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x);
        r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y);

        SDL_RenderCopy(renderer, bg.mTexture, nullptr, &r);
    }
}

void BackgroundSpriteComponent::SetBackgroundTextures(const std::vector<SDL_Texture*>& textures)
{
    int count = 0;
    for (auto texture : textures) {
        BackgroundTexture temp;
        temp.mTexture = texture;
        temp.mOffset.x = count * mScreenSize.x;
        temp.mOffset.y = 0;
        mBackgroundTextures.emplace_back(temp);
        ++count;
    }
}
