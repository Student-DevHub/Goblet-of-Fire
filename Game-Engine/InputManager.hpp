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
  using namespace Physics;
  namespace Input {
    class InputManager {
    public:
      static enum class Key {
        kW, kA, kS, kD,
        kUp, kDown, kLeft, kRight
      };

      static std::shared_ptr<Input::InputManager> getInstance();

      void update();

      bool isKeyPressed(InputManager::Key) const;
      bool isKeyDown(InputManager::Key) const;
      bool isKeyUp(InputManager::Key) const;

      bool leftMouseButton() const;
      bool rightMouseButton() const;
      point_2<int32_t> getMousePoint() const;

    private:
      InputManager();
      static std::shared_ptr<InputManager> instance_;
      static std::mutex instance_mut_;

      std::atomic<bool> focus;

      std::vector<std::unordered_map<InputManager::Key, bool>> key_status_;

      bool leftMouseButton, rightMouseButton;
      point_2<int32_t> mousePoint;
    };

    std::shared_ptr<InputManager> InputManager::instance_ = nullptr;
  }
}

#endif // !INPUT_MANAGER_HPP
