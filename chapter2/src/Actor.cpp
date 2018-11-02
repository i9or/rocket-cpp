#include "Actor.h"

#include "Actor.h"
#include "Component.h"
#include "Game.h"

#include <algorithm>

Actor::Actor(Game* game)
    : mState(EActive)
    , mPosition(Vector2::Zero)
    , mScale(1.0f)
    , mRotation(0.0f)
    , mGame(game) {
    mGame->AddActor(this);
}

Actor::~Actor() {
    mGame->RemoveActor(this);

    while (!mComponents.empty()) {
        delete mComponents.back();
    }
}

void Actor::Update(float deltaTime) {
    if (mState == EActive) {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime) {
    for (auto component : mComponents) {
        component->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime) {
}

void Actor::AddComponent(Component* component) {
    int componentOrder = component->GetUpdateOrder();
    auto iterator = mComponents.begin();
    for (; iterator != mComponents.end(); ++iterator) {
        if (componentOrder < (*iterator)->GetUpdateOrder()) {
            break;
        }
    }

    mComponents.insert(iterator, component);
}

void Actor::RemoveComponent(Component* component) {
    auto iterator = std::find(mComponents.begin(), mComponents.end(), component);
    if (iterator != mComponents.end()) {
        mComponents.erase(iterator);
    }
}
