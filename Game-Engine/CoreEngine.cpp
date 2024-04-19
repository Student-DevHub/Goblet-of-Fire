#include "CoreEngine.hpp"

namespace GobletOfFire {
  namespace Core {
    CoreEngine::CoreEngine() : stop_(false) {}

    void CoreEngine::init() {
      //create the scene manager and pass the shared_ptr of the engine
      //this was the reason for `std::enable_shared_from_this<Core::CoreEngine>`
      scene_manager_ = std::make_shared<Core::SceneManager>(shared_from_this()); 
      //create a pool of 4 threads
      engine_thread_pool_ = std::make_unique<Core::ThreadPool>(4); 

      calculateSuitableFPS();
    }

    void CoreEngine::calculateSuitableFPS() { 
      //no special implementation yet..
      target_frame_rate_ = 60; 
      frame_duration_ = std::chrono::milliseconds(1000 / 60);
    }

    void CoreEngine::run() {
      
      //assign threads the main components of the game
      engine_thread_pool_->enqueue([this] { scene_manager_->logicLoop(); });
      engine_thread_pool_->enqueue([this] { scene_manager_->renderLoop(); });
      engine_thread_pool_->enqueue([this] { processInputPoll(); });

      //maintain the frame duration and display the active buffer
      using namespace GobletOfFire::Utilities;
      while (!shouldStop()) {
        auto start_time = Time::clock::now();

        {
          //obtain the ownership of the `std::mutex`
          std::unique_lock<std::mutex> lock(window_creation_); 
          
          main_window_->beginDraw();
          auto ptr_texture = scene_manager_->getActiveBuffer();

          //make sure pointer isn't `nullptr`
          if (ptr_texture) { 
            sf::Sprite sprite_to_draw(ptr_texture->getTexture());
            main_window_->draw(sprite_to_draw);
          }

          main_window_->endDraw();
        }

        //if the task was completed before the frame duration, sleep for the remaining time
        auto time_elapsed = Utilities::Time::getTimeElapsed(start_time);
        auto remaining_time = frame_duration_ - time_elapsed;
        if (remaining_time > Time::duration(0)) {
          std::this_thread::sleep_for(remaining_time);
        }

      }
      //make sure to call the destructor of thread pool to join the threads before running the destructor of the engine itself
      engine_thread_pool_.reset(); 
    }

    void CoreEngine::stop() {
      stop_.store(true);
    }

    bool CoreEngine::shouldStop() const {
      return stop_.load();
    }

    void CoreEngine::processInputPoll() {
      sf::Event event;

      while (!shouldStop()) {
        main_window_->pollEvent(event);

        if (event.type == sf::Event::Closed) {
          stop();
          Input::InputManager::getInstance()->setFocus(false);
        }
        else if (event.type == sf::Event::LostFocus) {
          Input::InputManager::getInstance()->setFocus(false);
        }
        else if (event.type == sf::Event::GainedFocus) {
          Input::InputManager::getInstance()->setFocus(true);
        }

      }

    }

  }
}