#include "InputManager.hpp"

namespace GobletOfFire {
  namespace Input {

    InputManager::InputManager()
      : focus_(true), l_mouse_(false), r_mouse_(false), mouse_position_(-1, -1),
        key_status_(std::move(std::vector<keyMap>(2))), active_(0),
        window_ptr_(nullptr) {}

    void InputManager::addWindow(std::shared_ptr<Graphics::Window> window) {
      window_ptr_ = std::move(window);
    }

    std::shared_ptr<Input::InputManager> InputManager::getInstance() {
      static std::shared_ptr<InputManager> instance(new InputManager());
      return instance;
    }

    void InputManager::update() {
      active_ = active_ ^ 1;

      
      if(!getFocus()){
        clear();
        updateMousePointer();
      }
      else {
        updateKeyboard();
        updateMouse();
        updateMousePointer();
      }

    }

    void InputManager::updateKeyboard() {
      auto &map = key_status_[active_];
      {
        map[Key::kW] = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        map[Key::kA] = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        map[Key::kS] = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        map[Key::kD] = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        map[Key::kUp] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        map[Key::kDown] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        map[Key::kLeft] = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        map[Key::kRight] = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
      }
    }

    void InputManager::updateMouse() {
      l_mouse_ = sf::Mouse::isButtonPressed(sf::Mouse::Left);
      r_mouse_ = sf::Mouse::isButtonPressed(sf::Mouse::Right);
    }

    void InputManager::updateMousePointer() {
      auto mouse_position = sf::Mouse::getPosition();
      auto window_position = window_ptr_->getWindowPosition();
      auto window_size = window_ptr_->getWindowSize();

      if (!window_ptr_->isCreated()) {
        mouse_position_ = Physics::point2<int32_t>{ -1, -1 };
      }
      else { 
        mouse_position.x -= window_position.x;
        mouse_position.y -= window_position.y;

        bool insideWindow = (
          (mouse_position.x >= 0) && (mouse_position.x < window_size.x) &&
          (mouse_position.y >= 0) && (mouse_position.y < window_size.y));
        
        mouse_position_ = insideWindow ? 
          mouse_position : Physics::point2<int32_t>{-1, -1};
      }
    }

    void InputManager::clear() {
      auto& current_map = key_status_[active_];
      current_map.clear();

      l_mouse_ = false;
      r_mouse_ = false;
      mouse_position_ = Physics::point2<int32_t>{ -1, -1 };
    }

    bool InputManager::isKeyPressed(Key key) {
      auto& curr_map = key_status_[active_];
      auto& prev_map = key_status_[active_ ^ 1];

      // (false)' && (true)
      return (!prev_map[key]) && curr_map[key]; 
    }

    bool InputManager::isKeyReleased(Key key) {
      auto& curr_map = key_status_[active_];
      auto& prev_map = key_status_[active_ ^ 1];

      // (false)' && (true)
      return (!curr_map[key]) && prev_map[key];
    }

    bool InputManager::isKeyDown(Key key) {
      auto& curr_map = key_status_[active_];
      auto& prev_map = key_status_[active_ ^ 1];

      // (true) && (true)
      return curr_map[key] && prev_map[key];
    }

    bool InputManager::isKeyUp(Key key) {
      auto& curr_map = key_status_[active_];
      auto& prev_map = key_status_[active_ ^ 1];

      // (true)' && (true)' (NOR here)
      return !(curr_map[key] || prev_map[key]);
    }

    bool InputManager::leftMouseButton() const {
      return l_mouse_;
    }
    bool InputManager::rightMouseButton() const {
      return r_mouse_;
    }
    Physics::point2<int32_t> InputManager::getMousePoint() const {
      return mouse_position_;
    }

    //will be used by `CoreEngine`
    void InputManager::setFocus(bool focus) {
      focus_.store(focus);
    }

    bool InputManager::getFocus() const {
      return focus_.load();
    }
  }
}