#include "InputManager.hpp"

namespace GobletOfFire {
  namespace Input {
    InputManager::InputManager(const std::shared_ptr<Graphics::Window>& window_ptr)
      : focus_(true), 
        leftMouseButton_(false), rightMouseButton_(false), mousePoint_(-1, -1),
      key_status_(std::move(std::vector<keyMap>(2))), active_(0),
      window_ptr_(window_ptr) {}

    void InputManager::init(std::shared_ptr<Graphics::Window> window) {
        auto instance = std::make_shared<InputManager>((window));
        instance_= instance;
    }

    std::shared_ptr<Input::InputManager> InputManager::getInstance() {
      //load the instance and return
      return instance_.lock();
    }

    void InputManager::update() {
      //if the active is 1, make it 0, else make it 1
      active_ = active_ ^ 1;
      auto& current_map = key_status_[active_];

      //if the window is out of focus, turn of all the active keys, ignore the mouse buttons. 
      if(!getFocus()){
        key_status_[active_].clear();
        leftMouseButton_ = false;
        rightMouseButton_ = false;
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
      leftMouseButton_ = sf::Mouse::isButtonPressed(sf::Mouse::Left);
      rightMouseButton_ = sf::Mouse::isButtonPressed(sf::Mouse::Right);

      updateMousePointer();
    }

    void InputManager::updateMousePointer() {
      //getting mouse position relative to the window
      const auto& window = window_ptr_->getRenderWindow();
      auto mousePosition = sf::Mouse::getPosition(window);

      // Check if the mouse is inside the window
      bool insideWindow = (
        (mousePosition.x >= 0) && (mousePosition.x < window.getSize().x) &&
        (mousePosition.y >= 0) && (mousePosition.y < window.getSize().y));

      //if inside, move the pointer, else reset the coordinates
      mousePoint_ = insideWindow ?
        std::move(mousePosition) : std::move(Physics::point2<int32_t>{-1, -1});
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
      return leftMouseButton_;
    }
    bool InputManager::rightMouseButton() const {
      return rightMouseButton_;
    }
    Physics::point2<int32_t> InputManager::getMousePoint() const {
      return mousePoint_;
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