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

#include "Namespaces.ns.hpp"
#include "SceneManager.hpp"
#include "ThreadPool.hpp"
#include "TimeManager.hpp"

namespace GobletOfFire {
  namespace Core {

    class CoreEngine : public std::enable_shared_from_this<Core::CoreEngine> {
    public:
      CoreEngine(); //empty constructor. Maybe I will convert this class into singleton.

      void init(); //initialize the resources 
      void run(); //the main loop is on the main thread; it is responsible for showing the active buffer on the screen
      void stop(); //this will stop the engine

      bool shouldStop() const; //will be accessable to all the classes

    private:
      //this function will run some frames with heavy computations and long range loops
      //it will help the game to determine what is the prefered fps for the pc that is running the game
      void calculateSuitableFPS();

      //this function will detect global related inputs like resizing, window close, full screen etc.
      void processInputPoll();

      std::shared_ptr<Core::SceneManager> scene_manager_; 
      
      std::unique_ptr<Core::ThreadPool> engine_thread_pool_; //thread pool only for he engine
      std::shared_ptr<Graphics::Window> main_window_; //the main window of the game

      // I might change its position, maybe create a config struct? 
      uint32_t target_frame_rate_;
      std::chrono::milliseconds frame_duration_;

      std::atomic<bool> stop_; //the atomic variable to terminate the execution of the engine.
      std::mutex stop_mutex_; //to sync stop() and shouldStop() functions
    };

  }
}

#endif /* CORE_ENGINE_HPP */