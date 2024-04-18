#include "InputManager.hpp"

namespace GobletOfFire {
  using namespace Physics;
  namespace Input {
    InputManager::InputManager() 
      : focus(true), 
        leftMouseButton(false), rightMouseButton(false), mousePoint(-1, -1) {}

    std::shared_ptr<Input::InputManager> InputManager::getInstance() {
      std::unique_lock<std::mutex> lock(instance_mut_);
      if (!instance_) {
        instance_= std::make_shared<InputManager>();
      }

      return instance_;
    }

  }
}