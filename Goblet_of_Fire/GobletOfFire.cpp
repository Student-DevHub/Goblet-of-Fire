#include "GobletOfFire.h"
#include "TestingClasses.h"

namespace GobletOfFire {
  namespace CoreGame {
    GobletofFire::GobletofFire(const std::string& title, const sf::Vector2u& size) 
      : main_window_(std::make_shared<Graphics::Window>(title, size)) {
      std::cout << "Running main constructor!" << std::endl;
    }

    void GobletofFire::run() {
      //load the content from all the files using async from std::future
      loadFilesAsync(); //it is empty for now
      changeMagicScreen(std::make_shared<tests::TestingState>(shared_from_this(), main_window_));

      mainLoop();
    }

    void GobletofFire::changeMagicScreen(std::shared_ptr<CoreGame::MagicScreen> new_screen) {
      if (Ui_interface_thread) {
        current_magic_screen_->end();
        Ui_interface_thread->join();
      }

      current_magic_screen_ = new_screen;

      Ui_interface_thread = std::make_unique<std::jthread>([this]() {
                              current_magic_screen_->handleInput();
                            });
    }

    void GobletofFire::setMainGameStatus(bool gameStatus) {
      GobletOfFire::gameStatus = gameStatus;
    }

    void GobletofFire::loadFilesAsync() {}
    
    void GobletofFire::mainLoop() {
      while (gameStatus) {
        std::unique_lock<std::mutex> lock(Graphics::window_creation);
        main_window_->beginDraw();
        current_magic_screen_->renderEverything();
        main_window_->endDraw();
      }

      if (Ui_interface_thread) {
        current_magic_screen_->end();
        Ui_interface_thread->join();
      }
    }

  }
}
