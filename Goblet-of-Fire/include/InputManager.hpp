#pragma once
#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <memory>
#include <cstdint>

#include <SFML/Window.hpp>

#include "Graphics.hpp"
#include "Physics.hpp"

namespace GobletOfFire {
  namespace Input {
    class InputManager {
    public:
      enum class Key {
        kW = 0, kA, kS, kD, kF, k0,
        kUp, kDown, kLeft, kRight,
        kEnter
      };

      enum class MouseButton {
        kRight = static_cast<uint64_t>(Key::kEnter) + 1,
        kLeft
      };

      InputManager(std::shared_ptr<Graphics::window>);

      void update();

      bool isKeyPressed(Key) const;
      bool isKeyReleased(Key) const;
      bool isKeyHold(Key) const;

      bool isbuttonPressed(MouseButton) const;
      bool isbuttonReleased(MouseButton) const;
      bool isbuttonHold(MouseButton) const;

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

      void mapBit(uint32_t pos, bool status);
      bool checkBit(uint64_t map, uint64_t mask) const;

      uint64_t prev_map_;
      uint64_t curr_map_;

      std::shared_ptr<Graphics::window> window_ptr_;
      std::atomic<bool> focus_;

      Physics::point2<int32_t> mouse_position_;
    };
  }
}

#endif // !INPUT_MANAGER_HPP
