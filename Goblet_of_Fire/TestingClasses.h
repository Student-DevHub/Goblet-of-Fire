#pragma once
#ifndef TEST_H
#define TEST_H

#include <memory>
#include "Window.h"
#include "MagicScreen.h"
#include "GobletOfFire.namespace.h"

namespace GobletOfFire {
  namespace tests {
    class TestingState : public CoreGame::MagicScreen {
    public:
      TestingState(std::shared_ptr<CoreGame::GobletofFire> game_ptr, std::shared_ptr<Graphics::Window> main_window)
        : game_ptr_(game_ptr), main_window_(main_window), state_exist_(true) {}

      virtual void handleInput() override {
        while (state_exist_) {
          sf::Event event;
          if (!main_window_->getPollEvent(event)) continue;

          if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::M)
              game_ptr_->changeMagicScreen(std::make_shared<tests::TestingState>(game_ptr_, main_window_));
            else if (event.key.code == sf::Keyboard::F5)
              main_window_->toggleFullScreen();
          }
          if (event.type == sf::Event::Closed)
            GobletOfFire::gameStatus = false;
        }
      }

      virtual void end() override { state_exist_ = false; }

      virtual void renderEverything() override {
        main_window_->beginDraw();
        main_window_->endDraw();
      }

    private:
      std::shared_ptr<CoreGame::GobletofFire> game_ptr_;
      std::shared_ptr<Graphics::Window> main_window_;
      bool state_exist_;
    };
  }
}

#endif