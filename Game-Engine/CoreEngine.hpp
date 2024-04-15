#pragma once
#ifndef CORE_ENGINE_HPP
#define CORE_ENGINE_HPP

#include <memory>
#include <chrono>
#include <thread>
#include <atomic>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Namespaces.ns.hpp"
#include "SceneManager.hpp"

namespace GobletOfFire {
  namespace Core {

    class CoreEngine {
    public:
      CoreEngine();

      void init();
      void run();
      void stop();

    private:
      std::shared_ptr<Core::SceneManager> scene_manager_;

      int target_frame_rate_;
      std::chrono::milliseconds frame_duration_;

      std::atomic<bool> stop_;
    };

  }
}

#endif /* CORE_ENGINE_HPP */