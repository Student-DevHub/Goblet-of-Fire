#include "InputManager.hpp"

namespace GobletOfFire {
  namespace Input {

    InputManager::InputManager(std::shared_ptr<Graphics::window> window)
      : prev_map_(uint64_t(0)), curr_map_(uint64_t(0)), window_ptr_(window), focus_
      (true), mouse_position_{ -1, -1 } {}
    
    void InputManager::update() {
      prev_map_ = curr_map_;
      clear();

      if (getFocus()) {
        updateKeyboard();
        updateMouse();
      }

      updateMousePointer();
    }

    bool InputManager::isKeyPressed(Key key) const {
      auto pos = static_cast<uint64_t>(key);
      uint64_t mask = static_cast<uint64_t>(1) << pos;

      return (!checkBit(prev_map_, mask)) && checkBit(curr_map_, mask);
    }

    bool InputManager::isKeyReleased(Key key) const {
      auto pos = static_cast<uint64_t>(key);
      uint64_t mask = static_cast<uint64_t>(1) << pos;

      return (!checkBit(curr_map_, mask)) && checkBit(prev_map_, mask);
    }

    bool InputManager::isKeyHold(Key key) const {
      auto pos = static_cast<uint64_t>(key);
      uint64_t mask = static_cast<uint64_t>(1) << pos;

      return checkBit(prev_map_, mask) && checkBit(curr_map_, mask);
    }

    bool InputManager::isbuttonPressed(MouseButton button) const {
      auto pos = static_cast<uint64_t>(button);
      uint64_t mask = static_cast<uint64_t>(1) << pos;

      return (!checkBit(prev_map_, mask)) && checkBit(curr_map_, mask);
    }

    bool InputManager::isbuttonReleased(MouseButton button) const {
      auto pos = static_cast<uint64_t>(button);
      uint64_t mask = static_cast<uint64_t>(1) << pos;

      return (!checkBit(curr_map_, mask)) && checkBit(prev_map_, mask);
    }

    bool InputManager::isbuttonHold(MouseButton button) const {
      auto pos = static_cast<uint64_t>(button);
      uint64_t mask = static_cast<uint64_t>(1) << pos;

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
      mapBit(static_cast<uint32_t>(Key::kW), keyboard::isKeyPressed(keyboard::W));
      mapBit(static_cast<uint32_t>(Key::kA), keyboard::isKeyPressed(keyboard::A));
      mapBit(static_cast<uint32_t>(Key::kS), keyboard::isKeyPressed(keyboard::S));
      mapBit(static_cast<uint32_t>(Key::kD), keyboard::isKeyPressed(keyboard::D));
      mapBit(static_cast<uint32_t>(Key::kUp), keyboard::isKeyPressed(keyboard::Up));
      mapBit(static_cast<uint32_t>(Key::kDown), keyboard::isKeyPressed(keyboard::Down));
      mapBit(static_cast<uint32_t>(Key::kLeft), keyboard::isKeyPressed(keyboard::Left));
      mapBit(static_cast<uint32_t>(Key::kRight), keyboard::isKeyPressed(keyboard::Right));
      mapBit(static_cast<uint32_t>(Key::kEnter), keyboard::isKeyPressed(keyboard::Enter));
      mapBit(static_cast<uint32_t>(Key::kF), keyboard::isKeyPressed(keyboard::F));
      mapBit(static_cast<uint32_t>(Key::k0), keyboard::isKeyPressed(keyboard::Numpad0));
    }

    void InputManager::updateMouse() {
      mapBit(static_cast<uint32_t>(MouseButton::kLeft), mouse::isButtonPressed(mouse::Left));
      mapBit(static_cast<uint32_t>(MouseButton::kRight), mouse::isButtonPressed(mouse::Right));
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

    void InputManager::mapBit(uint32_t pos, bool status) {
      uint64_t map = 1;

      if (status)
        map = map << pos;
      else
        map = 0;

      curr_map_ |= map;
    }

    bool InputManager::checkBit(uint64_t map, uint64_t mask) const {
      return (map & mask) != 0;
    }
  }
}