#include "CoreEngine.hpp"
#include "Namespaces.ns.hpp"

namespace GobletOfFire {
  namespace Core {
    CoreEngine::CoreEngine() : stop_(false) {}

    void CoreEngine::init() {
      scene_manager_ = std::make_shared<SceneManager>();

      target_frame_rate_ = 60;
      frame_duration_ = std::chrono::milliseconds(1000 / target_frame_rate_);
    }

    void CoreEngine::run() {
      
      while (!stop) {
        auto start_time = std::chrono::steady_clock::now();

        scene_manager_->render();

        auto end_time = std::chrono::steady_clock::now();
        auto time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        auto remaining_time = frame_duration_ - time_taken;

        if (remaining_time >= std::chrono::milliseconds(0))
          std::this_thread::sleep_for(remaining_time);
      }
    }

    void CoreEngine::stop() {
      stop_ = true;
    }

  }
}