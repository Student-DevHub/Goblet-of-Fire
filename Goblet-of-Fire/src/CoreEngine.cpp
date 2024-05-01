#include "CoreEngine.hpp"

#include <iostream>


namespace GobletOfFire {
  namespace Core {
    std::shared_ptr<CoreEngine> CoreEngine::getInstance() {
      static std::shared_ptr<CoreEngine> instance(new CoreEngine);
      return instance;
    }

    CoreEngine::CoreEngine()
      : stop_(false), scene_manager_(nullptr),
      main_window_(nullptr), target_frame_rate_(1),
      frame_duration_(Utilities::Time::duration(1000))
      , input_handler_(nullptr) {}

    void CoreEngine::init() {
      main_window_ = std::make_shared<Graphics::window>(
        sf::VideoMode(1280, 720), "Window", sf::Style::Default);

      input_handler_ = std::make_shared<Input::InputManager>(main_window_);

      scene_manager_ = std::make_shared<Core::SceneManager>(
        shared_from_this(), input_handler_);

      calculateSuitableFPS();
    }

    void CoreEngine::calculateSuitableFPS() {
      target_frame_rate_ = 60;
      frame_duration_ = Utilities::Time::duration(1000 / target_frame_rate_);
      main_window_->setFramerateLimit(target_frame_rate_);
    }

    void CoreEngine::run() {

      while (main_window_->isOpen()) {
        this->displayWindow();
        input_handler_->update();
        scene_manager_->update();
        this->pollEvents();
      }
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
        sf::Sprite sprite_to_draw(ptr_texture->getTexture());
        main_window_->draw(sprite_to_draw);
      }

      main_window_->display();
    }

    void CoreEngine::wait(const Utilities::Time::timePoint& start_time) const {
      auto time_elapsed = Utilities::Time::getTimeElapsed(start_time);
      auto remaining_time = (frame_duration_ - time_elapsed) / 2;

      if (remaining_time > Utilities::Time::duration(0)) {
        std::this_thread::sleep_for(remaining_time);
      }

      time_elapsed = Utilities::Time::getTimeElapsed(start_time);
      std::cout << "Time elapsed: " << time_elapsed.count() << std::endl;
    }
  }
}