#ifndef SHIP_H
#define SHIP_H

#include "Actor.h"

class Ship : public Actor {
public:
    Ship(class Game* game);
    void UpdateActor(float deltaTime) override;
    void ProcessKeyboard(const uint8_t* state);

    float GetHorizontalSpeed() const {
        return mHorizontalSpeed;
    }

    float GetVerticalSpeed() const {
        return mVerticalSpeed;
    }

private:
    float mHorizontalSpeed;
    float mVerticalSpeed;
};

#endif // SHIP_H
