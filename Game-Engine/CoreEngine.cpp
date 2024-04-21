#include "CoreEngine.hpp"

namespace GobletOfFire {
  namespace Core {
    std::shared_ptr<CoreEngine> CoreEngine::getInstance() {
      static std::shared_ptr<CoreEngine> instance(new CoreEngine);
      return instance;
    }

    CoreEngine::CoreEngine()
      : stop_(false), scene_manager_(nullptr), engine_thread_pool_(nullptr),
      main_window_(nullptr), target_frame_rate_(1),
      frame_duration_(Utilities::Time::duration(1000)) {}

    void CoreEngine::init() {
      scene_manager_ = std::make_shared<Core::SceneManager>(
        shared_from_this());
      main_window_ = std::make_shared<Graphics::Window>(
        "Window", Physics::point2<std::uint32_t>(1280, 720));
      engine_thread_pool_ = std::make_unique<Core::ThreadPool>(2);
      
      Input::InputManager::getInstance()->addWindow(main_window_);

      calculateSuitableFPS();
    }

    void CoreEngine::calculateSuitableFPS() {
      target_frame_rate_ = 60;
      frame_duration_ = Utilities::Time::duration(1000 / target_frame_rate_);
    }

    void CoreEngine::run() {
      engine_thread_pool_->enqueue([this] { scene_manager_->logicLoop(); });
      engine_thread_pool_->enqueue([this] { scene_manager_->renderLoop(); });

      while (!shouldStop()) {
        auto start_time = Utilities::Time::clock::now();
        {
          std::unique_lock<std::mutex> lock(window_creation_);
          processInputPoll();
          displayWindow();
        }
        
        auto time_elapsed = Utilities::Time::getTimeElapsed(start_time);
        auto remaining_time = frame_duration_ - time_elapsed;

        if (remaining_time > Utilities::Time::duration(0)) {
          std::this_thread::sleep_for(remaining_time);
        }
      }
      
      engine_thread_pool_.reset();
    }

    bool CoreEngine::shouldStop() const { return stop_.load(); }
    void CoreEngine::stop() { stop_.store(true); }

    void CoreEngine::processInputPoll() {
      Input::inputEvent event;
      while (main_window_->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          stop();
        }
        else if (event.type == sf::Event::LostFocus) {
          Input::InputManager::getInstance()->setFocus(false);
        }
        else if (event.type == sf::Event::GainedFocus) {
          Input::InputManager::getInstance()->setFocus(true);
        }
      }
    }

    void CoreEngine::displayWindow() {
      main_window_->beginDraw();
      auto ptr_texture = scene_manager_->getActiveBuffer();

      if (ptr_texture) {
        sf::Sprite sprite_to_draw(ptr_texture->getTexture());
        main_window_->draw(sprite_to_draw);
      }

      main_window_->endDraw();
    }
  }
}