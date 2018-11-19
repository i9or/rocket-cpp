#ifndef ANIMATED_SPRITE_COMPONENT_H
#define ANIMATED_SPRITE_COMPONENT_H

#include "SpriteComponent.h"

#include <vector>

class AnimatedSpriteComponent : public SpriteComponent {
public:
    AnimatedSpriteComponent(class Actor* owner, int drawOrder = 100);

    void Update(float deltaTime) override;
    void SetAnimationTextures(const std::vector<SDL_Texture*>& textures);

    float GetAnimationFPS() const {
        return mAnimationFPS;
    }

    void SetAnimationFPS(float fps) {
        mAnimationFPS = fps;
    }

private:
    std::vector<SDL_Texture*> mAnimationTextures;
    float mCurrentFrame;
    float mAnimationFPS;
};

#endif // ANIMATED_SPRITE_COMPONENT_H
