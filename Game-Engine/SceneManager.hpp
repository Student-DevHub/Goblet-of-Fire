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

#include "Namespaces.ns.hpp"
#include "CoreEngine.hpp"
#include "Scene.hpp"

namespace GobletOfFire {
  namespace Core {
    class SceneManager : public std::enable_shared_from_this<Core::SceneManager> {
    public:
      SceneManager(const std::shared_ptr<Core::CoreEngine>&);
      ~SceneManager() {} //empty for now

      //these loops will run in two different threads. 
      //this could also have been done in a single thread but before shaping it this way, I had a different plan in my mind
      void logicLoop(); //update the logic of the scene
      void renderLoop(); //render the scene in it's buffer

      static enum class Scenes {
        kNone,
        kMainMenu, 
        kCharacterSelection,
        kMapSelection,
        k1v1, 
        kPause,
        kResult
      };

      std::shared_ptr<sf::RenderTexture> getActiveBuffer() const;
      void updateActiveBuffer();

      void addNewScene(std::pair<Scenes, std::unique_ptr<Core::Scene>>&);
      void switchTo(SceneManager::Scenes);
      void remove(SceneManager::Scenes);

    private:
      std::shared_ptr<Core::CoreEngine> main_engine_;

      std::unordered_map<SceneManager::Scenes, std::unique_ptr<Core::Scene>> scenes_;
      SceneManager::Scenes current_scene_;
      mutable std::mutex scene_change_mut_;

      std::shared_ptr<sf::RenderTexture> active_buffer_;
      mutable std::mutex update_buffer_mut_;
      std::condition_variable update_buffer_cv_;

      std::atomic<bool> logic_status_;
      std::atomic<bool> render_status_;
      std::condition_variable update_cv_;
      mutable std::mutex update_mut_;
    };
  }
}

#endif /* SCENE_MANAGER_HPP */