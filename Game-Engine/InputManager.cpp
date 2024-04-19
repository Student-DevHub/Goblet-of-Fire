#include "InputManager.hpp"

namespace GobletOfFire {
  using namespace Physics;
  namespace Input {
    InputManager::InputManager(std::shared_ptr<Graphics::Window> window_ptr)
      : focus_(true), 
        leftMouseButton_(false), rightMouseButton_(false), mousePoint_(-1, -1),
      key_status_(std::move(std::vector<keyMap>(2))), active_(0),
      window_ptr_(window_ptr) {}

    std::shared_ptr<Input::InputManager> InputManager::getInstance() {
      if (!instance_.load()) {
        auto instance = std::make_shared<InputManager>();
        instance_.store(instance);
      }

      return instance_.load();
    }

    void InputManager::update() {
      active_ = active_ ^ 1;

      if(!focus_.load()){
        key_status_[active_].clear();
        leftMouseButton_ = false;
        rightMouseButton_ = false;
      }

      auto& current_map = key_status_[active_];

      using kyb = sf::Keyboard;
      current_map[Key::kW] = kyb::isKeyPressed(kyb::W);
      current_map[Key::kA] = kyb::isKeyPressed(kyb::A);
      current_map[Key::kS] = kyb::isKeyPressed(kyb::S);
      current_map[Key::kD] = kyb::isKeyPressed(kyb::D);
      current_map[Key::kUp] = kyb::isKeyPressed(kyb::Up);
      current_map[Key::kDown] = kyb::isKeyPressed(kyb::Down);
      current_map[Key::kLeft] = kyb::isKeyPressed(kyb::Left);
      current_map[Key::kRight] = kyb::isKeyPressed(kyb::Right);

      using ms = sf::Mouse;
      leftMouseButton_ = ms::isButtonPressed(ms::Left);
      rightMouseButton_ = ms::isButtonPressed(ms::Right);

      const auto& window = window_ptr_->getRenderWindow();
      auto mousePosition = sf::Mouse::getPosition(window);

      // Check if the mouse is inside the window
      bool insideWindow = (
        mousePosition.x >= 0 && mousePosition.x < window.getSize().x &&
        mousePosition.y >= 0 && mousePosition.y < window.getSize().y);

      mousePoint_ = insideWindow ? 
        std::move(mousePosition) : std::move(Physics::point2<int32_t>{-1, -1});
    }

    bool InputManager::isKeyPressed(Key key) {
      auto& curr_map = key_status_[active_];
      auto& prev_map = key_status_[active_ ^ 1];

      return (!prev_map[key]) && curr_map[key];
    }

    bool InputManager::isKeyReleased(Key key) {
      auto& curr_map = key_status_[active_];
      auto& prev_map = key_status_[active_ ^ 1];


      return (!curr_map[key]) && prev_map[key];
    }

    bool InputManager::isKeyDown(Key key) {
      auto& curr_map = key_status_[active_];
      auto& prev_map = key_status_[active_ ^ 1];

      return curr_map[key] && prev_map[key];
    }

    bool InputManager::isKeyUp(Key key) {
      auto& curr_map = key_status_[active_];
      auto& prev_map = key_status_[active_ ^ 1];

      return !(curr_map[key] || prev_map[key]);
    }
  }
}