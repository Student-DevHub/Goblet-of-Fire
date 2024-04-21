#pragma once
#ifndef CORE_ENGINE_HPP
#define CORE_ENGINE_HPP

#include <memory>
#include <cstdint>
#include <chrono>
#include <thread>
#include <atomic>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Core.hpp"
#include "Graphics.hpp"
#include "Utilities.hpp"
#include "Input.hpp"

namespace GobletOfFire {
  namespace Core {

    class CoreEngine : public std::enable_shared_from_this<Core::CoreEngine> {
    public:
      
      static std::shared_ptr<CoreEngine> getInstance();

      CoreEngine(const CoreEngine&) = delete;
      ~CoreEngine() {}

      void init();
      void run();
      bool shouldStop() const;
      void stop();

    private:
      CoreEngine();
      void calculateSuitableFPS();

      void processInputPoll();
      void displayWindow();

      std::shared_ptr<Core::SceneManager> scene_manager_;
      std::unique_ptr<Core::ThreadPool> engine_thread_pool_;
      std::shared_ptr<Graphics::Window> main_window_;
      std::mutex window_creation_;

      uint32_t target_frame_rate_;
      Utilities::Time::duration frame_duration_;

      std::atomic<bool> stop_;

    };

  }
}

#endif /* CORE_ENGINE_HPP */