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

    {
      auto player = std::make_shared<ObjectComponent::Object>(4);
      using compType = ObjectComponent::iComponent::Type;

      auto transform = std::make_shared<ObjectComponent::cTransform>(593.f, 485.f);
      player->addComponent(compType::kTransform, transform);

      auto health = std::make_shared<ObjectComponent::cHealth>();
      player->addComponent(ObjectComponent::iComponent::Type::kHealth, health);

      auto health_bar = std::make_shared<ObjectComponent::HealthBar>(1);
      health_bar->subscribe(health.get());
      auto health_obj = std::make_shared<ObjectComponent::HealthBarObjectAdapter>(health_bar);
      object_collection_->add(health_obj);


      ObjectComponent::cCollision::CollisionBox box;
      box.offset_.x = 20.f;
      box.offset_.y = 16.f;
      box.d_.x = 23.f;
      box.d_.y = 33.f;

      auto collision = std::make_shared<ObjectComponent::PlayerCollision>(
        player, quadtree_, box
      );
      player->addComponent(ObjectComponent::iComponent::Type::kCollision, collision);

      auto physics = std::make_shared<ObjectComponent::cPhysics>(player, Physics::point2<float>(400.f, 400.f), 45.f, 520.f);
      physics->setAcceleration({ 0.f, 520.f });
      player->addComponent(compType::kPhysics, physics);

      auto sprite = std::make_shared<ObjectComponent::cSprite>(1, player);
      sprite->setScale(1.5, 1.5);
      player->addComponent(compType::kSprite, sprite);

      auto kb = std::make_shared<ObjectComponent::cKeyboardMovement>(player, input_manager_);
      kb->changeKeyBind(1, Input::InputManager::Key::kUp);
      kb->changeKeyBind(2, Input::InputManager::Key::kLeft);
      kb->changeKeyBind(3, Input::InputManager::Key::kRight);
      player->addComponent(compType::kMovement, kb);

      auto animation = std::make_shared<ObjectComponent::cAnimation>(player);
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
      player->addComponent(compType::kAnimation, animation);

      object_collection_->add(player);
    }

    {
      auto player = std::make_shared<ObjectComponent::Object>(4);
      using compType = ObjectComponent::iComponent::Type;

      auto transform = std::make_shared<ObjectComponent::cTransform>(593.f, 485.f);
      player->addComponent(compType::kTransform, transform);

      auto health = std::make_shared<ObjectComponent::cHealth>();
      player->addComponent(ObjectComponent::iComponent::Type::kHealth, health);

      auto health_bar = std::make_shared<ObjectComponent::HealthBar>(2);
      health_bar->subscribe(health.get());
      auto health_obj = std::make_shared<ObjectComponent::HealthBarObjectAdapter>(health_bar);
      object_collection_->add(health_obj);

      ObjectComponent::cCollision::CollisionBox box;
      box.offset_.x = 20.f;
      box.offset_.y = 16.f;
      box.d_.x = 23.f;
      box.d_.y = 33.f;

      auto collision = std::make_shared<ObjectComponent::PlayerCollision>(
        player, quadtree_, box
      );
      player->addComponent(ObjectComponent::iComponent::Type::kCollision, collision);

      auto physics = std::make_shared<ObjectComponent::cPhysics>(player, Physics::point2<float>(400.f, 400.f), 45.f, 520.f);
      physics->setAcceleration({ 0.f, 520.f });
      player->addComponent(compType::kPhysics, physics);

      auto sprite = std::make_shared<ObjectComponent::cSprite>(1, player);
      sprite->setScale(1.5, 1.5);
      player->addComponent(compType::kSprite, sprite);

      auto kb = std::make_shared<ObjectComponent::cKeyboardMovement>(player, input_manager_);
      kb->changeKeyBind(1, Input::InputManager::Key::kW);
      kb->changeKeyBind(2, Input::InputManager::Key::kA);
      kb->changeKeyBind(3, Input::InputManager::Key::kD);
      player->addComponent(compType::kMovement, kb);

      auto animation = std::make_shared<ObjectComponent::cAnimation>(player);
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
      player->addComponent(compType::kAnimation, animation);

      object_collection_->add(player);
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
    processExit();
    object_collection_->processRemovals();
    object_collection_->processAddition();
    object_collection_->update(compType::kMovement, dt);
    object_collection_->update(compType::kPhysics, dt);
    object_collection_->update(compType::kAnimation, dt);
    quadtree_->update();
    object_collection_->update(compType::kCollision, dt);
    object_collection_->update(compType::kSprite, dt);
    //update healthbar logic here
    last_update_ = Utilities::Time::clock::now();
  }

  void MainGame::updateRender() {
    local_buffer_->clear(Graphics::color::Black);
    object_collection_->render(*local_buffer_);
    //render healthbars. 
    local_buffer_->display();
  }

  std::shared_ptr<Graphics::buffer> MainGame::getBuffer() const{
    return local_buffer_;
  }

  void MainGame::processExit() {
    if (input_manager_->isKeyPressed(Input::InputManager::Key::kEnter)) {
      scene_manager_.lock()->switchTo(1);
    }
  }
}