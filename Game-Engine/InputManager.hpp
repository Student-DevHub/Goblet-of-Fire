#pragma once
#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <memory>
#include <unordered_map>
#include <mutex>
#include <cstdint>

#include <SFML/Window.hpp>

#include "Graphics.hpp"

namespace GobletOfFire {
  namespace Input {
    class InputManager {
    public:
      enum class Key {
        kW, kA, kS, kD,
        kUp, kDown, kLeft, kRight
      };

      static std::shared_ptr<Input::InputManager> getInstance();

      void addWindow(std::shared_ptr<Graphics::Window> window);
      void update();

      bool isKeyPressed(Key);
      bool isKeyReleased(Key);
      bool isKeyUp(Key);
      bool isKeyDown(Key);

      bool leftMouseButton() const;
      bool rightMouseButton() const;
      Physics::point2<int32_t> getMousePoint() const;

      void setFocus(bool);
      bool getFocus() const;

    private:
      void updateKeyboard();
      void updateMouse();
      void updateMousePointer();
      void clear();

      InputManager();

      std::shared_ptr<Graphics::Window> window_ptr_; 
      std::atomic<bool> focus_;

      using keyMap = std::unordered_map<Key, bool>;
      std::vector<keyMap> key_status_;
      std::uint32_t active_ : 1; 

      bool l_mouse_, r_mouse_; 
      Physics::point2<int32_t> mouse_position_;
    };
  }
}

#endif // !INPUT_MANAGER_HPP
