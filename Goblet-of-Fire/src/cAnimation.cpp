#include "cAnimation.hpp"

namespace GobletOfFire::ObjectComponent {
  cAnimation::FrameData::FrameData(Physics::point2<int32_t> origin,
    Physics::point2<int32_t> size,
    Utilities::Time::duration display_time)
    : origin_(origin), size_(size), display_time_(display_time) {}

  cAnimation::Animation::Animation(FacingDirection direction)
    : current_frame_index_(0u),
    current_frame_time_(Utilities::Time::duration(0)),
    direction_(direction) {}

  void cAnimation::Animation::addFrame(FrameData frame) {
    frames_.push_back(frame);
  }

  cAnimation::FrameData cAnimation::Animation::getCurrentFrame() const {
    return frames_.at(current_frame_index_);
  }

  bool cAnimation::Animation::updateFrame(const Utilities::Time::duration dt) {
    current_frame_time_ = std::chrono::duration_cast<Utilities::Time::duration>(
      current_frame_time_ + dt);
    
    if (current_frame_time_ >= getCurrentFrame().display_time_) {
      current_frame_time_ = std::chrono::duration_cast<Utilities::Time::duration>(
        current_frame_time_ - getCurrentFrame().display_time_
      );
      incrementFrame();

      return true;
    }

    return false;
  }

  void cAnimation::Animation::reset() {
    current_frame_index_ = 0u;
    current_frame_time_ = Utilities::Time::duration(0);
  }

  void cAnimation::Animation::changeDirection(FacingDirection direction) {
    if (direction_ != direction)
    {
      direction_ = direction;
      std::for_each(frames_.begin(), frames_.end(), [](FrameData& frame) {
        frame.origin_.x += frame.size_.x;
        frame.size_.x *= -1;
        });
    }
  }

  cAnimation::FacingDirection cAnimation::Animation::getDirection() const {
    return direction_;
  }

  void cAnimation::Animation::incrementFrame() {
    current_frame_index_++;
    current_frame_index_ %= frames_.size();
  }


  cAnimation::cAnimation(std::shared_ptr<iObject> owner)
    : owner_(owner), current_state_(AnimationState::kNone) {}

  void cAnimation::create() {
    if (owner_.expired()) {
      throw std::runtime_error("Owner of cSprite is expired!");
    }

    auto ptr = std::dynamic_pointer_cast<cSprite>(owner_.lock()->getComponent(iComponent::Type::kSprite));
    if (!ptr)
      throw std::runtime_error("Pointer not casted to cTransform in cSprite");

    sprite_ = ptr;

  }

  void cAnimation::destroy() { animations_.clear(); }

  void cAnimation::activate() {}
  void cAnimation::deActivate() {}

  void cAnimation::update(const Utilities::Time::duration dt) {
    if (current_state_ == AnimationState::kNone) {
      return;
    }
    if (!animations_[current_state_]->updateFrame(dt)) {
      return;
    }

    auto data = animations_[current_state_]->getCurrentFrame();
    if (sprite_.expired()) {
      throw std::runtime_error("cSprite is expired!");
    }

    sprite_.lock()->setTextureRect(data.origin_, data.size_);
  }

  void cAnimation::render(Graphics::buffer&) {}

  void cAnimation::addAnimation(AnimationState state, std::unique_ptr<Animation> animation) {
    animations_.emplace(std::make_pair(state, std::move(animation)));
  }

  void cAnimation::setAnimationState(AnimationState state) {
    auto it = animations_.find(state);
    if (it == animations_.end()) {
      throw std::runtime_error("Animation state wasn't found!");
    }
    if (current_state_ != AnimationState::kNone) {
      it->second->changeDirection(animations_[current_state_]->getDirection());
      animations_[current_state_]->reset();
    }

    current_state_ = it->first;
  }

  const cAnimation::AnimationState cAnimation::getAnimationState() const {
    return current_state_;
  }

  void cAnimation::changeDirection(FacingDirection direction) {
    if (current_state_ != AnimationState::kNone) {
      animations_[current_state_]->changeDirection(direction);
    }
  }

}