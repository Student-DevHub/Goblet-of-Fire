#include "InputManager.hpp"

namespace GobletOfFire {
  namespace Input {

    InputManager::InputManager(std::shared_ptr<Graphics::window> window)
      : prev_map_(std::uint64_t(0)), curr_map_(std::uint64_t(0)), window_ptr_(window), focus_
      (true), mouse_position_{ -1, -1 } {}
    
    void InputManager::update() {
      prev_map_ = curr_map_;
      curr_map_ = 0;

      if (focus_.load()) {
        updateKeyboard();
        updateMouse();
      }

      updateMousePointer();
    }

    bool InputManager::isKeyPressed(Key key) const {
      auto pos = static_cast<uint64_t>(key);
      std::uint64_t mask = static_cast<uint64_t>(1) << pos;

      return (!checkBit(prev_map_, mask)) && checkBit(curr_map_, mask);
    }

    bool InputManager::isKeyReleased(Key key) const {
      auto pos = static_cast<uint64_t>(key);
      std::uint64_t mask = static_cast<uint64_t>(1) << pos;

      return (!checkBit(curr_map_, mask)) && checkBit(prev_map_, mask);
    }

    bool InputManager::isKeyHold(Key key) const {
      auto pos = static_cast<uint64_t>(key);
      std::uint64_t mask = static_cast<uint64_t>(1) << pos;

      return checkBit(prev_map_, mask) && checkBit(curr_map_, mask);
    }

    bool InputManager::buttonPressed(MouseButton button) const {
      auto pos = static_cast<uint64_t>(button);
      std::uint64_t mask = static_cast<uint64_t>(1) << pos;

      return (!checkBit(prev_map_, mask)) && checkBit(curr_map_, mask);
    }

    bool InputManager::buttonReleased(MouseButton button) const {
      auto pos = static_cast<uint64_t>(button);
      std::uint64_t mask = static_cast<uint64_t>(1) << pos;

      return (!checkBit(curr_map_, mask)) && checkBit(prev_map_, mask);
    }

    bool InputManager::buttonHold(MouseButton button) const {
      auto pos = static_cast<uint64_t>(button);
      std::uint64_t mask = static_cast<uint64_t>(1) << pos;

      return checkBit(prev_map_, mask) && checkBit(curr_map_, mask);
    }

    Physics::point2<int32_t> InputManager::getMousePoint() const {
      return mouse_position_;
    }

    void InputManager::setFocus(bool focus) {
      focus_.store(focus);
    }

    bool InputManager::getFocus() const {
      return focus_.load();
    }

    void InputManager::updateKeyboard() {
      curr_map_ |= keyboard::isKeyPressed(sf::Keyboard::W) ? static_cast<uint64_t>(Key::kW) : 0;
      curr_map_ |= keyboard::isKeyPressed(sf::Keyboard::A) ? static_cast<uint64_t>(Key::kA) : 0;
      curr_map_ |= keyboard::isKeyPressed(sf::Keyboard::S) ? static_cast<uint64_t>(Key::kS) : 0;
      curr_map_ |= keyboard::isKeyPressed(sf::Keyboard::D) ? static_cast<uint64_t>(Key::kD) : 0;
      curr_map_ |= keyboard::isKeyPressed(sf::Keyboard::Up) ? static_cast<uint64_t>(Key::kUp) : 0;
      curr_map_ |= keyboard::isKeyPressed(sf::Keyboard::Down) ? static_cast<uint64_t>(Key::kDown) : 0;
      curr_map_ |= keyboard::isKeyPressed(sf::Keyboard::Left) ? static_cast<uint64_t>(Key::kLeft) : 0;
      curr_map_ |= keyboard::isKeyPressed(sf::Keyboard::Right) ? static_cast<uint64_t>(Key::kRight) : 0;
    }

    void InputManager::updateMouse() {
      curr_map_ |= mouse::isButtonPressed(sf::Mouse::Left) ? static_cast<uint64_t>(MouseButton::kLeft) : 0;

      curr_map_ |= mouse::isButtonPressed(sf::Mouse::Right) ? static_cast<uint64_t>(MouseButton::kRight) : 0;
    }

    void InputManager::updateMousePointer() {
      auto mouse_position = mouse::getPosition(*window_ptr_);
      auto window_size = window_ptr_->getSize();

      bool insideWindow = (mouse_position.x >= 0 && mouse_position.x < window_size.x &&
        mouse_position.y >= 0 && mouse_position.y < window_size.y);

      mouse_position_ = insideWindow ?
        Physics::point2<int32_t>{ mouse_position.x, mouse_position.y } :
        Physics::point2<int32_t>{ -1, -1 };
    }

    void InputManager::clear() {
      curr_map_ = 0;
    }

    void InputManager::mapBit(std::uint32_t map, bool status) {
      if (status) {
        curr_map_ |= map;
      }
      else {
        curr_map_ &= ~map;
      }
    }

    bool InputManager::checkBit(std::uint64_t map, std::uint64_t mask) const {
      return (map & mask) != 0;
    }

  }
}