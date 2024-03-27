#include "GobletOfFire.h"

namespace GobletOfFire {
  namespace CoreGame {
    GobletofFire::GobletofFire(const std::string& title = "Goblet of Fire", const sf::Vector2u& size = { 1280, 720 }) 
      : main_window_(std::make_shared<Graphics::Window>(title, size)) {
      std::cout << "Running main constructor!" << std::endl;
    }

    void GobletofFire::run() {
      //load the content from all the files using async from std::future
      loadFilesAsync(); //it is empty for now
      current_state_ = std::make_shared<tests::TestingState>(shared_from_this(), main_window_);

      io_thread = std::move(std::make_unique<std::jthread>(&tests::TestingState::handleInput, current_state_.get()));
      
      mainLoop();
    }
  }
}
