#pragma once
#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <memory>
#include <cstdint>

#include <SFML/Window.hpp>

#include "Graphics.hpp"

namespace GobletOfFire {
  namespace Input {
    class InputManager {
    public:
      enum class Key {
        kW = 1, kA, kS, kD,
        kUp, kDown, kLeft, kRight
      };

      enum class MouseButton {
        kRight = static_cast<std::uint64_t>(Key::kRight) + 1, 
        kLeft
      };

      InputManager(std::shared_ptr<Graphics::window>);

      void update();

      bool isKeyPressed(Key) const;
      bool isKeyReleased(Key) const;
      bool isKeyHold(Key) const;

      bool buttonPressed(MouseButton) const;
      bool buttonReleased(MouseButton) const;
      bool buttonHold(MouseButton) const;

      Physics::point2<int32_t> getMousePoint() const;

      void setFocus(bool);
      bool getFocus() const;

    private:
      using mouse = sf::Mouse;
      using keyboard = sf::Keyboard;

      void updateKeyboard();
      void updateMouse();
      void updateMousePointer();
      void clear();

      void mapBit(std::uint32_t map, bool status);
      bool checkBit(std::uint64_t map, std::uint64_t mask) const;

      std::uint64_t prev_map_;
      std::uint64_t curr_map_;

      std::shared_ptr<Graphics::window> window_ptr_; 
      std::atomic<bool> focus_; 

      Physics::point2<int32_t> mouse_position_;
    };
  }
}

#endif // !INPUT_MANAGER_HPP
