#include "CoreEngine.hpp"

namespace GobletOfFire {
  namespace Core {
    CoreEngine::CoreEngine() : stop_(false) {}

    void CoreEngine::init() {
      scene_manager_ = std::make_shared<Core::SceneManager>(shared_from_this()); //create the scene manager and pass the shared_ptr of the engine
      engine_thread_pool_ = std::make_unique<Core::ThreadPool>(4); //create a pool of 4 threads

      calculateSuitableFPS();
    }

    void CoreEngine::calculateSuitableFPS() { //no special implementation yet..
      target_frame_rate_ = 60; 
      frame_duration_ = std::chrono::milliseconds(1000 / 60);
    }

    void CoreEngine::run() {
      
      engine_thread_pool_->enqueue([this] { scene_manager_->logicLoop(); });
      engine_thread_pool_->enqueue([this] { scene_manager_->renderLoop(); });

      //maintain the frame duration and display the active buffer
      while (!stop) {
        auto start_time = clock::now();

        {
          main_window_->beginDraw();
          auto ptr_texture = scene_manager_->getActiveBuffer();

          if (ptr_texture) { //make sure pointer isn't `nullptr`
            sf::Sprite sprite_to_draw(ptr_texture->getTexture());
            main_window_->draw(sprite_to_draw);
          }

          main_window_->endDraw();
        }

        //if the task was completed before the frame duration, sleep for the remaining time
        auto time_elapsed = Utilities::TimeManager::getTimeElapsed(start_time);
        auto remaining_time = frame_duration_ - time_elapsed;

        if (remaining_time >= std::chrono::milliseconds(0))
          std::this_thread::sleep_for(remaining_time);
      }
    }

    void CoreEngine::stop() {
      std::unique_lock<std::mutex> lock(stop_mutex_);
      stop_ = true;
    }

    bool CoreEngine::shouldStop() const {
      std::unique_lock<std::mutex> lock(stop_mutex_);
      return stop_;
    }
  }
}