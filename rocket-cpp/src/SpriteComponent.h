#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "Component.h"

#include "SDL.h"

class SpriteComponent : public Component {
public:
    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(SDL_Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture);

    int GetDrawOrder() const {
        return mDrawOrder;
    }

    int GetTextureWidth() const {
        return mTextureWidth;
    }

    int GetTextureHeight() const {
        return mTextureHeight;
    }

protected:
    SDL_Texture* mTexture;
    int mDrawOrder;
    int mTextureWidth;
    int mTextureHeight;
};

#endif // SPRITE_COMPONENT_H
