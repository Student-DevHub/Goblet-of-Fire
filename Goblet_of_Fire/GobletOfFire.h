#pragma once
#ifndef GOBLET_OF_FIRE
#define GOBLET_OF_FIRE

#include <string> //essentials
#include <memory>
#include <iostream>
#include <thread> //concurrent programming
#include <future>
#include <mutex>
#include <SFML/Window.hpp> //sfml libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "GobletOfFire.namespace.h"
#include "Window.h" //custom headers
#include "GameState.h"

namespace GobletOfFire {


  namespace CoreGame {
    class GobletofFire : public std::enable_shared_from_this<GobletofFire> {
    public: 
      GobletofFire(const std::string& = "Goblet of Fire", const sf::Vector2u& = { 1280, 720 });
      void run();
      
      void changeGameState(std::shared_ptr<CoreGame::GameState>);
      void setMainGameStatus(bool = false);

    private:
      void loadFilesAsync();
      void mainLoop();
      
      std::shared_ptr<Graphics::Window> main_window_;
      std::shared_ptr<CoreGame::GameState> current_state_;
      std::unique_ptr<std::jthread> io_thread;
    };
  }

}

#endif
