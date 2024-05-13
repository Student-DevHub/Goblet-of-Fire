#include "MainGame.hpp"

namespace GobletOfFire::Scene {
  MainGame::MainGame(
    std::shared_ptr<Core::SceneManager> scene_manager,
    std::shared_ptr<Input::InputManager> input)
    : input_manager_(input), scene_manager_(scene_manager) {}

  void MainGame::create() {
    quadtree_ = std::make_shared<Physics::QuadTree>();
    object_collection_ = std::make_unique<ObjectComponent::ObjectCollection>();

    local_buffer_ = std::make_shared<Graphics::buffer>();
    local_buffer_->create(Physics::window_dimensions_.x, Physics::window_dimensions_.y);

    t_resource_manager_ = Core::ResourceManager<Graphics::texture>::getInstance();

    std::shared_ptr<ObjectComponent::Object> player1;
    std::shared_ptr<ObjectComponent::Object> player2;

    {
      player1 = std::make_shared<ObjectComponent::Object>(4);
      using compType = ObjectComponent::iComponent::Type;

      auto transform = std::make_shared<ObjectComponent::cTransform>(593.f, 485.f);
      player1->addComponent(compType::kTransform, transform);

      p1 = std::make_shared<ObjectComponent::cHealth>();
      player1->addComponent(ObjectComponent::iComponent::Type::kHealth, p1);

      auto health_bar = std::make_shared<ObjectComponent::HealthBar>(1);
      p1->attach(health_bar);
      auto health_obj = std::make_shared<ObjectComponent::HealthBarObjectAdapter>(health_bar);
      object_collection_->add(health_obj);


      ObjectComponent::cCollision::CollisionBox box;
      box.offset_.x = 20.f;
      box.offset_.y = 16.f;
      box.d_.x = 23.f;
      box.d_.y = 33.f;

      auto collision = std::make_shared<ObjectComponent::PlayerCollision>(
        player1, quadtree_, box
      );
      player1->addComponent(ObjectComponent::iComponent::Type::kCollision, collision);

      auto physics = std::make_shared<ObjectComponent::cPhysics>(player1, Physics::point2<float>(400.f, 400.f), 45.f, 520.f);
      physics->setAcceleration({ 0.f, 520.f });
      player1->addComponent(compType::kPhysics, physics);

      auto sprite = std::make_shared<ObjectComponent::cSprite>(1, player1);
      sprite->setScale(1.5, 1.5);
      player1->addComponent(compType::kSprite, sprite);

      auto animation = std::make_shared<ObjectComponent::cAnimation>(player1);
      {
        auto animation_1 = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_1->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 0 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_1->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 0 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_1->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 0 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_1->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 3, 65 * 0 }, { 65, 65 }, Utilities::Time::duration(50)));

        animation->addAnimation(1, std::move(animation_1));
      }

      {
        auto animation_2 = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 3, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 4, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 5, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 6, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 7, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 8, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));

        animation->addAnimation(2, std::move(animation_2));
      }

      {
        auto animation_ = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 2 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 2 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 2 }, { 65, 65 }, Utilities::Time::duration(50)));

        animation->addAnimation(3, std::move(animation_));
      }

      {
        auto animation_ = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 3 }, { 65, 60 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 3 }, { 65, 60 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 3 }, { 65, 60 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 3, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 4, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 5, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 6, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 7, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 8, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 9, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(150)));

        animation->addAnimation(4, std::move(animation_));
      }

      {
        auto animation_ = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 4 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 4 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 4 }, { 65, 65 }, Utilities::Time::duration(50)));

        animation->addAnimation(5, std::move(animation_));
      }

      {
        auto animation_ = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 3, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 4, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 5, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 6, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(50)));

        animation->addAnimation(6, std::move(animation_));
      }
      animation->setAnimationState(4);
      player1->addComponent(compType::kAnimation, animation);

      object_collection_->add(player1);
    }

    {
      player2 = std::make_shared<ObjectComponent::Object>(4);
      using compType = ObjectComponent::iComponent::Type;

      auto transform = std::make_shared<ObjectComponent::cTransform>(593.f, 485.f);
      player2->addComponent(compType::kTransform, transform);

      p2 = std::make_shared<ObjectComponent::cHealth>();
      player2->addComponent(ObjectComponent::iComponent::Type::kHealth, p2);

      auto health_bar = std::make_shared<ObjectComponent::HealthBar>(2);
      p2->attach(health_bar);
      auto health_obj = std::make_shared<ObjectComponent::HealthBarObjectAdapter>(health_bar);
      object_collection_->add(health_obj);

      ObjectComponent::cCollision::CollisionBox box;
      box.offset_.x = 20.f;
      box.offset_.y = 16.f;
      box.d_.x = 23.f;
      box.d_.y = 33.f;

      auto collision = std::make_shared<ObjectComponent::PlayerCollision>(
        player2, quadtree_, box
      );
      player2->addComponent(ObjectComponent::iComponent::Type::kCollision, collision);

      auto physics = std::make_shared<ObjectComponent::cPhysics>(player2, Physics::point2<float>(400.f, 400.f), 45.f, 520.f);
      physics->setAcceleration({ 0.f, 520.f });
      player2->addComponent(compType::kPhysics, physics);

      auto sprite = std::make_shared<ObjectComponent::cSprite>(1, player2);
      sprite->setScale(1.5, 1.5);
      player2->addComponent(compType::kSprite, sprite);

      auto animation = std::make_shared<ObjectComponent::cAnimation>(player2);
      {
        auto animation_1 = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_1->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 0 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_1->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 0 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_1->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 0 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_1->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 3, 65 * 0 }, { 65, 65 }, Utilities::Time::duration(50)));

        animation->addAnimation(1, std::move(animation_1));
      }

      {
        auto animation_2 = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 3, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 4, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 5, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 6, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 7, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_2->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 8, 65 * 1 }, { 65, 65 }, Utilities::Time::duration(50)));

        animation->addAnimation(2, std::move(animation_2));
      }

      {
        auto animation_ = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 2 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 2 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 2 }, { 65, 65 }, Utilities::Time::duration(50)));

        animation->addAnimation(3, std::move(animation_));
      }

      {
        auto animation_ = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 3 }, { 65, 60 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 3 }, { 65, 60 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 3 }, { 65, 60 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 3, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 4, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 5, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 6, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 7, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 8, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(150)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 9, 65 * 3 }, { 65, 65 }, Utilities::Time::duration(150)));

        animation->addAnimation(4, std::move(animation_));
      }

      {
        auto animation_ = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 4 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 4 }, { 65, 65 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 4 }, { 65, 65 }, Utilities::Time::duration(50)));

        animation->addAnimation(5, std::move(animation_));
      }

      {
        auto animation_ = std::make_unique<ObjectComponent::cAnimation::Animation>(ObjectComponent::cAnimation::FacingDirection::kRight);

        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 0, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 1, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 2, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 3, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 4, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 5, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(50)));
        animation_->addFrame(ObjectComponent::cAnimation::FrameData({ 65 * 6, 65 * 5 }, { 65, 71 }, Utilities::Time::duration(50)));

        animation->addAnimation(6, std::move(animation_));
      }
      animation->setAnimationState(4);
      player2->addComponent(compType::kAnimation, animation);

      object_collection_->add(player2);
    }

    {
      auto kb = std::make_shared<ObjectComponent::cKeyboardMovement>(player2, input_manager_, player1);
      kb->changeKeyBind(1, Input::InputManager::Key::kUp);
      kb->changeKeyBind(2, Input::InputManager::Key::kLeft);
      kb->changeKeyBind(3, Input::InputManager::Key::kRight);
      kb->changeKeyBind(4, Input::InputManager::Key::k0);
      player2->addComponent(ObjectComponent::iComponent::Type::kMovement, kb);
    }

    {
      auto kb = std::make_shared<ObjectComponent::cKeyboardMovement>(player1, input_manager_, player2);
      kb->changeKeyBind(1, Input::InputManager::Key::kW);
      kb->changeKeyBind(2, Input::InputManager::Key::kA);
      kb->changeKeyBind(3, Input::InputManager::Key::kD);
      kb->changeKeyBind(4, Input::InputManager::Key::kF);
      player1->addComponent(ObjectComponent::iComponent::Type::kMovement, kb);
    }

    {
      auto map = std::make_shared<ObjectComponent::Object>();

      auto sprite = std::make_shared<ObjectComponent::cSprite>(50, map);
      auto transform = std::make_shared<ObjectComponent::cTransform>(0.f, 0.f);
      map->addComponent(ObjectComponent::iComponent::Type::kSprite, sprite);
      map->addComponent(ObjectComponent::iComponent::Type::kTransform, transform);
      
      object_collection_->add(map);
    }

    {
      auto map = std::make_shared<ObjectComponent::Object>(5);

      auto sprite = std::make_shared<ObjectComponent::cSprite>(51, map);
      auto transform = std::make_shared<ObjectComponent::cTransform>(0.f, 0.f);
      map->addComponent(ObjectComponent::iComponent::Type::kSprite, sprite);
      map->addComponent(ObjectComponent::iComponent::Type::kTransform, transform);

      ObjectComponent::cCollision::CollisionBox box;
      box.offset_.x = 0.f;
      box.offset_.y = 570.f - 40.f;
      box.d_.x = 1279.7f;
      box.d_.y = 142.f + 40;

      auto collision = std::make_shared<ObjectComponent::LedgeCollision>(map, quadtree_, box);
      map->addComponent(ObjectComponent::iComponent::Type::kCollision, collision);

      object_collection_->add(map);
    }

    {
      auto ledge = std::make_shared<ObjectComponent::Object>(5);
      auto transform = std::make_shared<ObjectComponent::cTransform>(81.f, 305.f);
      ledge->addComponent(ObjectComponent::iComponent::Type::kTransform, transform);
      ObjectComponent::cCollision::CollisionBox box;
      box.offset_.x = 0.f;
      box.offset_.y = -35.f;
      box.d_.x = 266.f;
      box.d_.y = 29.f + 35.f;
      auto collision = std::make_shared<ObjectComponent::LedgeCollision>(ledge, quadtree_, box);
      ledge->addComponent(ObjectComponent::iComponent::Type::kCollision, collision);

      object_collection_->add(ledge);
    }
    {
      auto ledge = std::make_shared<ObjectComponent::Object>(5);
      auto transform = std::make_shared<ObjectComponent::cTransform>(914.f, 305.f);
      ledge->addComponent(ObjectComponent::iComponent::Type::kTransform, transform);
      ObjectComponent::cCollision::CollisionBox box;
      box.offset_.x = 0.f;
      box.offset_.y = -35.f;
      box.d_.x = 266.f;
      box.d_.y = 29.f + 35.f;
      auto collision = std::make_shared<ObjectComponent::LedgeCollision>(ledge, quadtree_, box);
      ledge->addComponent(ObjectComponent::iComponent::Type::kCollision, collision);

      object_collection_->add(ledge);
    }
    {
      auto ledge = std::make_shared<ObjectComponent::Object>(5);
      auto transform = std::make_shared<ObjectComponent::cTransform>(505.f, 156.f);
      ledge->addComponent(ObjectComponent::iComponent::Type::kTransform, transform);
      ObjectComponent::cCollision::CollisionBox box;
      box.offset_.x = 0.f;
      box.offset_.y = -35.f;
      box.d_.x = 266.f;
      box.d_.y = 29.f + 35.f;
      auto collision = std::make_shared<ObjectComponent::LedgeCollision>(ledge, quadtree_, box);
      ledge->addComponent(ObjectComponent::iComponent::Type::kCollision, collision);

      object_collection_->add(ledge);
    }
    {
      auto ledge = std::make_shared<ObjectComponent::Object>(5);
      auto transform = std::make_shared<ObjectComponent::cTransform>(505, 415.f);
      ledge->addComponent(ObjectComponent::iComponent::Type::kTransform, transform);
      ObjectComponent::cCollision::CollisionBox box;
      box.offset_.x = 0.f;
      box.offset_.y = -35.f;
      box.d_.x = 266.f;
      box.d_.y = 29.f + 35.f;
      auto collision = std::make_shared<ObjectComponent::LedgeCollision>(ledge, quadtree_, box);
      ledge->addComponent(ObjectComponent::iComponent::Type::kCollision, collision);

      object_collection_->add(ledge);
    }

    {
      auto map = std::make_shared<ObjectComponent::Object>(5);

      auto sprite = std::make_shared<ObjectComponent::cSprite>(52, map);
      auto transform = std::make_shared<ObjectComponent::cTransform>(0.f, 0.f);
      map->addComponent(ObjectComponent::iComponent::Type::kSprite, sprite);
      map->addComponent(ObjectComponent::iComponent::Type::kTransform, transform);

      object_collection_->add(map);
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
    object_collection_->processRemovals();
    object_collection_->processAddition();
    object_collection_->update(compType::kMovement, dt);
    object_collection_->update(compType::kPhysics, dt);
    object_collection_->update(compType::kAnimation, dt);
    quadtree_->update();
    object_collection_->update(compType::kCollision, dt);
    object_collection_->update(compType::kSprite, dt);
    last_update_ = Utilities::Time::clock::now();
    checkWinner();
  }

  void MainGame::updateRender() {
    local_buffer_->clear(Graphics::color::Black);
    object_collection_->render(*local_buffer_);
    local_buffer_->display();
  }

  std::shared_ptr<Graphics::buffer> MainGame::getBuffer() const{
    return local_buffer_;
  }

  void MainGame::checkWinner() {
    if (p1->getHealth() <= 0.0) {
      scene_manager_.lock()->switchTo(5);
    }
    else if (p2->getHealth() <= 0.0) {
      scene_manager_.lock()->switchTo(6);
    }
  }
}