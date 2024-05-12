#pragma once

#include "Component.h"
#include "Animation.h"
#include "C_Sprite.h"
#include "Object.h"

#include <iostream>

enum class AnimationState
{
    None,
    Idle,
    Walk
};

class C_Animation : public Component 
{
public:
    C_Animation(Object* owner);

    void awake() override;
    void update(float dt) override;

    void addAnimation(AnimationState state, std::shared_ptr<Animation> animation);

    void setAnimationState(AnimationState state);

    const AnimationState& getAnimationState() const;

private:
    std::shared_ptr<C_Sprite> sprite;
    std::map<AnimationState, std::shared_ptr<Animation>> animations;

    std::pair<AnimationState, std::shared_ptr<Animation>> currentAnimation;

};

