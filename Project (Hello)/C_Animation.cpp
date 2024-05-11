#include "C_Animation.h"

C_Animation::C_Animation(Object* owner)
	: Component(owner), currentAnimation(AnimationState::None, nullptr)
{
}

void C_Animation::awake()
{
	sprite = owner->GetComponent<C_Sprite>();
}

void C_Animation::update(float dt)
{
    if (currentAnimation.first != AnimationState::None)
    {
        bool newFrame = currentAnimation.second->updateFrame(dt);

        if (newFrame)
        {
            const FrameData* data = currentAnimation.second->getCurrentFrame();

            sprite->load(data->id); 

            sprite->SetTextureRect(data->x, data->y, data->width, data->height);
        }
    }
}

void C_Animation::addAnimation(AnimationState state, std::shared_ptr<Animation> animation)
{    
    auto inserted = animations.insert(std::make_pair(state, animation));

    if (currentAnimation.first == AnimationState::None)
    {
        setAnimationState(state);
    }
}

void C_Animation::setAnimationState(AnimationState state)
{
    // Set an animation of it is not already our current animation.
    if (currentAnimation.first == state)
    {
        return;
    }

    auto animation = animations.find(state);
    if (animation != animations.end())
    {
        currentAnimation.first = animation->first;
        currentAnimation.second = animation->second;

        currentAnimation.second->reset();
    }
}

const AnimationState& C_Animation::getAnimationState() const
{
    // Returns out current animation state.We can use this
    // to compare the objects current state to a desired state.
    return currentAnimation.first;
}


