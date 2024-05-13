#include "CoreEngine.hpp"

namespace GobletOfFire {
  namespace Core {

    CoreEngine::CoreEngine()
      : stop_(false), scene_manager_(nullptr),
      main_window_(nullptr), target_frame_rate_(1),
      frame_duration_(Utilities::Time::duration(1000))
      , input_handler_(nullptr) {}

    void CoreEngine::init() {
      main_window_ = std::make_shared<Graphics::window>(
        sf::VideoMode(1280, 720), "Goblet Of Fire", sf::Style::Default);

      input_handler_ = std::make_shared<Input::InputManager>(main_window_);

      scene_manager_ = std::make_shared<Core::SceneManager>(
        shared_from_this(), input_handler_);
      scene_manager_->init();

      calculateSuitableFPS();
    }

    void CoreEngine::calculateSuitableFPS() {
      target_frame_rate_ = 60;
      frame_duration_ = Utilities::Time::duration(1000 / target_frame_rate_);
      main_window_->setFramerateLimit(target_frame_rate_);
    }

    void CoreEngine::run() {

      while (main_window_->isOpen() && !stop_.load()) {
        this->displayWindow();
        input_handler_->update();
        scene_manager_->update();
        this->pollEvents();
      }

      if (!stop_.load()) {
        main_window_->close();
      }
    }

    void CoreEngine::stop() {
      stop_.store(true);
    }

    void CoreEngine::pollEvents() {
      Input::inputEvent event;
      while (main_window_->pollEvent(event)) {
        if (event.type == Input::inputEvent::Closed) {
          main_window_->close();
        }
        else if (event.type == sf::Event::LostFocus) {
          input_handler_->setFocus(false);
        }
        else if (event.type == sf::Event::GainedFocus) {
          input_handler_->setFocus(true);
        }
      }
    }

    void CoreEngine::displayWindow() {
      main_window_->clear();
      auto ptr_texture = scene_manager_->getActiveBuffer();

      if (ptr_texture) {
        Graphics::sprite sprite_to_draw(ptr_texture->getTexture());
        //sprite_to_draw.setTextureRect(ObjectComponent::cSprite::spriteRect(0, ptr_texture->getSize().y, ptr_texture->getSize().x, -1 * ptr_texture->getSize().y));
        main_window_->draw(sprite_to_draw);
      }

      main_window_->display();
    }
  }
}