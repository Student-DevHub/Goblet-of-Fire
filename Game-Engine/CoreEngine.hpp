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

    private:
      CoreEngine();
      void calculateSuitableFPS();

      void pollEvents();
      void displayWindow();
      void wait(const Utilities::Time::timePoint&) const;

      std::shared_ptr<Core::SceneManager> scene_manager_;
      std::shared_ptr<Input::InputManager> input_handler_;
      std::shared_ptr<Graphics::window> main_window_;

      uint32_t target_frame_rate_;
      Utilities::Time::duration frame_duration_;

      std::atomic<bool> stop_;

    };

  }
}

#endif /* CORE_ENGINE_HPP */