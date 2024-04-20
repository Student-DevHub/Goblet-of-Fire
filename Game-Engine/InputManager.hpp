#pragma once
#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <memory>
#include <unordered_map>
#include <mutex>
#include <cstdint>

#include <SFML/Window.hpp>

#include "Namespaces.ns.hpp"
#include "Window.hpp"

namespace GobletOfFire {
  namespace Input {
    class InputManager {
    public:
      static enum class Key {
        kW, kA, kS, kD,
        kUp, kDown, kLeft, kRight
      };

      static std::shared_ptr<Input::InputManager> getInstance();

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
      //update the inputs (helper functions)
      void updateKeyboard(std::unordered_map<Key, bool>&);
      void updateMouse();
      void updateMousePointer();

      InputManager(std::shared_ptr<Graphics::Window>);
      static std::atomic<std::shared_ptr<InputManager>> instance_; //to share a single instance of the `InputManager` everywhere in the program
      std::shared_ptr<Graphics::Window> window_ptr_; //
      std::atomic<bool> focus_; //`true` if the window is focused else `false`

      using keyMap = std::unordered_map<Key, bool>;
      std::vector<keyMap> key_status_; //two `std::unordered_map` to add KeyReleased function
      std::uint32_t active_ : 1; //1-bit unsigned integer current `keyMap`

      bool leftMouseButton_, rightMouseButton_; //flags for mouse buttons
      Physics::point2<int32_t> mousePoint_;
    };

    std::atomic<std::shared_ptr<InputManager>> InputManager::instance_(nullptr); //no copy constructor for `std::atomic` 
  }
}

#endif // !INPUT_MANAGER_HPP
