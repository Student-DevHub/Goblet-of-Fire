#pragma once
#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <memory>
#include <cstdint>
#include <unordered_map>
#include <mutex>
#include <atomic>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Namespaces.ns.hpp"
#include "Window.hpp"
#include "Scene.hpp"

namespace GobletOfFire {
  namespace Core {
    class SceneManager : public std::enable_shared_from_this<Core::SceneManager> {
    public:
      SceneManager();

      void logicLoop();
      void renderLoop();

      std::shared_ptr<sf::RenderTexture> getActiveBuffer() const;
      void updateActiveBuffer();

      std::uint32_t addNewScene(std::shared_ptr<Core::Scene>);
      void switchTo(std::uint32_t);
      void remove(std::uint32_t);

    private:
      std::shared_ptr<Graphics::Window> main_window_;

      //unordered_map seemed better cuz we can instantiate the scenes without executing them just after inserting
      std::unordered_map<std::uint32_t, std::shared_ptr<Core::Scene>> scenes_;
      std::uint32_t current_scene_;

      static std::atomic<std::uint32_t> scene_id_tracker_;

      std::mutex window_creation_;
      std::mutex scene_change_;

    };

    std::atomic<std::uint32_t> SceneManager::scene_id_tracker_ = 0;
  }
}

#endif /* SCENE_MANAGER_HPP */