#pragma once
#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <iostream>

#include <memory>
#include <unordered_map>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <cstdint>

#include <SFML/Graphics.hpp>

namespace GobletOfFire {
  namespace Core {
    class CoreEngine;
  }
}

#include "T_CoreEngine.h"
#include "T_Scene.h"

namespace GobletOfFire {
  namespace Core {
    class SceneManager : public std::enable_shared_from_this<Core::SceneManager> {
    public:
      SceneManager(const std::shared_ptr<CoreEngine>&);
      ~SceneManager() {} //empty for now

      //these loops will run in two different threads. 
      //this could also have been done in a single thread but before shaping it this way, I had a different plan in my mind
      void logicLoop(); //update the logic of the scene 
      void renderLoop(); //render the scene in it's buffer

      //key for different scenes, may be moved to Scene::
      enum class Scene {
        kNone,
        kMainMenu,
        kCharacterSelection,
        kMapSelection,
        k1v1,
        kPause,
        kResult
      };

      //get the active sf::RenderTexture 
      std::shared_ptr<sf::RenderTexture> getActiveBuffer() const;
      //get the buffer from the current scene and update the active buffer
      void updateActiveBuffer();

      //pretty straight forward thing...
      void addNewScene(std::pair<Scene, std::shared_ptr<Scenes::Scene>>&);
      void switchTo(SceneManager::Scene);
      void remove(SceneManager::Scene);

    private:
      //shared reference of the main_engine...
      std::shared_ptr<Core::CoreEngine> main_engine_;

      //shared references of the scenes, mapped by scene enum
      std::unordered_map<
        SceneManager::Scene,
        std::shared_ptr<Scenes::Scene>> scenes_;

      SceneManager::Scene current_scene_;
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