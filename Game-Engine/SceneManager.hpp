#pragma once
#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <memory>
#include <unordered_map>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <cstdint>

#include <SFML/Graphics.hpp>

#include "Core.hpp"
#include "Scenes.hpp"

namespace GobletOfFire {
  namespace Core {
    class SceneManager : public std::enable_shared_from_this<Core::SceneManager> {
    public:
      SceneManager(const std::shared_ptr<CoreEngine>&);
      ~SceneManager() {}

      void logicLoop(); 
      void renderLoop();

      enum class Scene {
        kNone,
        kMainMenu,
        kCharacterSelection,
        kMapSelection,
        k1v1,
        kPause,
        kResult,
        kTest
      };

      std::shared_ptr<sf::RenderTexture> getActiveBuffer() const;
      void updateActiveBuffer();

      void addNewScene(const std::pair<Scene, std::shared_ptr<Scenes::Scene>>&);
      void switchTo(SceneManager::Scene);
      void remove(SceneManager::Scene);

    private:
      std::shared_ptr<Core::CoreEngine> main_engine_;

      std::unordered_map<
        SceneManager::Scene,
        std::shared_ptr<Scenes::Scene>> scenes_;  

      SceneManager::Scene current_scene_;
      mutable std::mutex scene_change_mut_;

      std::shared_ptr<sf::RenderTexture> active_buffer_;
      mutable std::mutex update_buffer_mut_;

      std::atomic<bool> logic_status_;
      std::atomic<bool> render_status_;
      std::condition_variable update_cv_;
      mutable std::mutex update_mut_;
    };
  }
}

#endif /* SCENE_MANAGER_HPP */