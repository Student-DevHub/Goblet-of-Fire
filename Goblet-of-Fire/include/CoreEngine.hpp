#pragma once
#ifndef CORE_ENGINE_HPP
#define CORE_ENGINE_HPP

#include <memory>
#include <cstdint>
#include <atomic>

#include <Core.hpp>
#include <Graphics.hpp>
#include <Utilities.hpp>
#include <Input.hpp>
#include <Design_patterns.hpp>

namespace GobletOfFire {
  namespace Core {

    class CoreEngine : public std::enable_shared_from_this<CoreEngine>, 
      public DesignPatterns::Singleton<CoreEngine> {
    public:
      friend class DesignPatterns::Singleton<CoreEngine>;

      CoreEngine(const CoreEngine&) = delete;
      ~CoreEngine() {}

      void init();
      void run();
      void stop();

    private:
      CoreEngine();
      void calculateSuitableFPS();

      void pollEvents();
      void displayWindow();

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