#include "MainGame.hpp"

namespace GobletOfFire::Scene {
  MainGame::MainGame(
    std::shared_ptr<Core::SceneManager> scene_manager,
    std::shared_ptr<Input::InputManager> input)
    : input_manager_(input), scene_manager_(scene_manager) {}

  void MainGame::create() {
    object_collection_ = std::make_unique<ObjectComponent::ObjectCollection>();

    local_buffer_ = std::make_unique<Graphics::buffer>();
    local_buffer_->create(Physics::window_dimensions_.x, Physics::window_dimensions_.y);

    t_resource_manager_ = Core::ResourceManager<Graphics::texture>::getInstance();

    {
      auto player = std::make_shared<ObjectComponent::Object>();
      using compType = ObjectComponent::iComponent::Type;

      auto transform = std::make_shared<ObjectComponent::cTransform>(10.f, 10.f);
      player->addComponent(compType::kTransform, transform);

      auto sprite = std::make_shared<ObjectComponent::cSprite>(1, player);
      player->addComponent(compType::kSprite, sprite);

      auto kb = std::make_shared<ObjectComponent::cKeyboardMovement>(player, input_manager_);
      kb->changeKeyBind(1, Input::InputManager::Key::kLeft);
      kb->changeKeyBind(2, Input::InputManager::Key::kRight);
      kb->changeKeyBind(3, Input::InputManager::Key::kUp);
      player->addComponent(compType::kMovement, kb);

      auto animation = std::make_shared<ObjectComponent::cAnimation>(player);
      {
        auto animation_1 = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_1->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 0 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_1->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 0 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_1->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 0 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_1->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 3, 65 * 0 }, { 65, 65 }, Utilities::Time::duration(200)));

        animation->addAnimation(1, std::move(animation_1));
      }

      {
        auto animation_2 = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 3, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 4, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 5, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 6, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 7, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 8, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(200)));

        animation->addAnimation(2, std::move(animation_2));
      }

      {
        auto animation_ = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 2 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 2 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 2 }, { 65, 65 }, Utilities::Time::duration(200)));

        animation->addAnimation(3, std::move(animation_));
      }

      {
        auto animation_ = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 3, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 4, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 5, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 6, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 7, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 8, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 9, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(200)));

        animation->addAnimation(4, std::move(animation_));
      }

      {
        auto animation_ = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 4 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 4 }, { 65, 65 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 4 }, { 65, 65 }, Utilities::Time::duration(200)));

        animation->addAnimation(5, std::move(animation_));
      }

      {
        auto animation_ = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 3, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 4, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 5, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(200)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 6, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(200)));

        animation->addAnimation(6, std::move(animation_));
      }
      player->addComponent(compType::kAnimation, animation);

      object_collection_->add(player);
    }
  }

  void MainGame::destroy() {}

  void MainGame::activate() {
    object_collection_->processAddition();
    last_update_ = Utilities::Time::clock::now();
  }

  void MainGame::deactivate() {}

  void MainGame::updateLogic() {
    using compType = ObjectComponent::iComponent::Type;

    auto dt = Utilities::Time::getTimeElapsed(last_update_);
    object_collection_->update(compType::kMovement, dt);
    object_collection_->processAddition();
    object_collection_->processRemovals();
    object_collection_->update(compType::kAnimation, dt);
    last_update_ = Utilities::Time::clock::now();
  }

  void MainGame::updateRender() {
    object_collection_->render(*local_buffer_);
  }

  std::shared_ptr<Graphics::buffer> MainGame::getBuffer() const{
    return local_buffer_;
  }

  void MainGame::processExit() {
    if (input_manager_->isKeyPressed(Input::InputManager::Key::kW)) {
      scene_manager_.lock()->switchTo(1);
    }
  }
}