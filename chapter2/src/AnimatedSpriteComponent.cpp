#include "AnimatedSpriteComponent.h"
#include "Math.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(Actor* owner, int drawOrder)
    : SpriteComponent(owner, drawOrder)
    , mCurrentFrame(0.0f)
    , mAnimationFPS(24.0f)
{
}

void AnimatedSpriteComponent::Update(float deltaTime)
{
    SpriteComponent::Update(deltaTime);

    if (mAnimationTextures.size() > 0) {
        mCurrentFrame += mAnimationFPS * deltaTime;

        while (mCurrentFrame >= mAnimationTextures.size()) {
            mCurrentFrame -= mAnimationTextures.size();
        }

        SetTexture(mAnimationTextures[static_cast<int>(mCurrentFrame)]);
    }
}

void AnimatedSpriteComponent::SetAnimationTextures(const std::vector<SDL_Texture*>& textures)
{
    mAnimationTextures = textures;

    if (mAnimationTextures.size() > 0) {
        mCurrentFrame = 0.0f;
        SetTexture(mAnimationTextures[0]);
    }
}
