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
      //empty constructor. Maybe I will convert this class into singleton.
      CoreEngine();
      //empty for now
      ~CoreEngine() {}

      //initialize the resources 
      void init();
      //the main loop is on the main thread; it is responsible for showing the active buffer on the screen
      void run();

      //will be accessable to scene manager
      inline bool shouldStop() const;

    private:
      //this will stop the engine
      //reason for privatizing this function was that I was taking the 
      inline void stop();

      //this function will run some frames with heavy computations and long range loops
      //it will help the game to determine what is the prefered fps for the pc that is running the game
      void calculateSuitableFPS();

      //helper functions for the main thread loop
      void processInputPoll();
      void displayWindow();

      //Manages the sequences of the scene and active buffer
      //also contains the logic and render loops
      //the reference is to be shared by the scenes; hence made `std::shared_ptr`
      std::shared_ptr<Core::SceneManager> scene_manager_;

      //thread pool ONLY for he engine
      std::unique_ptr<Core::ThreadPool> engine_thread_pool_;
      //the main window of the game
      //other classes to have the shared reference of the window
      std::shared_ptr<Graphics::Window> main_window_;
      //to control the `Window::toggleFullScreen()` and updating the window
      std::mutex window_creation_;

      // I might change its position, maybe create a config struct? 
      uint32_t target_frame_rate_;
      Utilities::Time::duration frame_duration_{};

      //the atomic variable to terminate the execution of the engine.
      //it will be accessed by different classes so should be made `std::atomic` to prevent data races
      std::atomic<bool> stop_;

    };

  }
}

#endif /* CORE_ENGINE_HPP */