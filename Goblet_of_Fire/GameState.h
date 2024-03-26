#pragma once
#ifndef GAME_STATE
#define GAME_STATE

#include <string>
#include <memory>
#include <iostream>
#include <thread>
#include "GobletOfFire.h"
#include "Window.h"

namespace GobletOfFire {
  namespace CoreGame {
    class GameState {
    public:
      virtual void handleInput() = 0;
      virtual void end() = 0;
      virtual void renderEverything() = 0;
    };

    class TestingState : public GameState {
    public:
      TestingState(std::shared_ptr<CoreGame::GobletofFire> game_ptr, std::shared_ptr<Window> main_window)
        : game_ptr_(game_ptr), main_window_(main_window), state_exist_(true) {}

      virtual void handleInput() override {
        while (state_exist_) {
          sf::Event event;
          if (!main_window_->getPollEvent(event)) continue;

          if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::M)
              game_ptr_->changeGameState(std::make_shared<CoreGame::TestingState>(game_ptr_, main_window_));
            else if (event.key.code == sf::Keyboard::F5)
              main_window_->toggleFullScreen();
          }
          
        }
      }

      virtual void end() override { state_exist_ = false; }
      
      virtual void renderEverything() override {
        main_window_->beginDraw();
        main_window_->endDraw();
      }

    private:
      std::shared_ptr<CoreGame::GobletofFire> game_ptr_;
      std::shared_ptr<Window> main_window_;
      bool state_exist_;
    };
  }
}
#endif