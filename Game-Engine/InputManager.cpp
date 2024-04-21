#include "InputManager.hpp"

namespace GobletOfFire {
  namespace Input {
    std::shared_ptr<InputManager> InputManager::instance_{ nullptr };

    InputManager::InputManager(const std::shared_ptr<Graphics::Window>& window_ptr)
      : focus_(true), 
        l_mouse_(false), r_mouse_(false), mouse_position_(-1, -1),
        key_status_(std::move(std::vector<keyMap>(2))), active_(0),
        window_ptr_(window_ptr) {}

    void InputManager::init(std::shared_ptr<Graphics::Window> window) {
      std::shared_ptr<InputManager> i(new InputManager(window));
      instance_ = std::move(i);
    }

    std::shared_ptr<Input::InputManager> InputManager::getInstance() {
      //load the instance and return
      return instance_;
    }

    void InputManager::update() {
      //if the active is 1, make it 0, else make it 1
      active_ = active_ ^ 1;
      auto& current_map = key_status_[active_];

      //if window is not created (means closed), then clear all inputs. 
      if (!window_ptr_->isCreated()) {
        clear();
      }

      //if the window is out of focus, turn of all the active keys, ignore the mouse buttons. 
      if(!getFocus()){
        key_status_[active_].clear();
        l_mouse_ = false;
        r_mouse_ = false;
        //mouse pointer can't be ignored cuz we can do hover animation if we want to even if the window is out of focus
        updateMousePointer();
        return;
      }

      updateKeyboard(current_map);
      updateMouse();
    }

    void InputManager::updateKeyboard(std::unordered_map<Key, bool>& map) {
      //update all the keys
      map[Key::kW] = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
      map[Key::kA] = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
      map[Key::kS] = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
      map[Key::kD] = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
      map[Key::kUp] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
      map[Key::kDown] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
      map[Key::kLeft] = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
      map[Key::kRight] = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    }

    void InputManager::updateMouse() {
      //update mouse buttons and pointer
      l_mouse_ = sf::Mouse::isButtonPressed(sf::Mouse::Left);
      r_mouse_ = sf::Mouse::isButtonPressed(sf::Mouse::Right);

      updateMousePointer();
    }

    void InputManager::updateMousePointer() {
      //getting mouse position relative to the window
      auto mouse_position = sf::Mouse::getPosition();
      auto window_position = window_ptr_->getWindowPosition();
      auto window_size = window_ptr_->getWindowSize();

      //if window is destroyed already
      if (window_position.x == window_position.y && window_position.x == -1) {
        mouse_position_ = Physics::point2<int32_t>{ -1, -1 };
      }
      //if window is not destroyed, but need to find if the position is within the window...
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
      // Clear all the keys in the current key status map
      auto& current_map = key_status_[active_];
      current_map.clear();

      // Reset mouse button states and position
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