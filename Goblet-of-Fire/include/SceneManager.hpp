#pragma once
#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <memory>
#include <unordered_map>
#include <cstdint>

#include <SFML/Graphics.hpp>

#include "Core.hpp"
#include <Scene.hpp>
#include <Input.hpp>

namespace GobletOfFire {
  namespace Core {
    
    class SceneManager : public std::enable_shared_from_this<Core::SceneManager> {
    public:
      SceneManager(const std::shared_ptr<CoreEngine>&, const std::shared_ptr<Input::InputManager>&);
      ~SceneManager() {}

      void update();

      enum class Scenes {
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

      void addNewScene(const std::pair<Scenes, std::shared_ptr<Scene::iScene>>&);
      void switchTo(SceneManager::Scenes);
      void remove(SceneManager::Scenes);

    private:


      std::shared_ptr<Core::CoreEngine> main_engine_;
      std::shared_ptr<Input::InputManager> input_handler_;

      std::unordered_map<
        SceneManager::Scenes,
        std::shared_ptr<Scene::iScene>> scenes_;  

      SceneManager::Scenes current_scene_;

      std::shared_ptr <Graphics::buffer> active_buffer_;
    };

  }
}

#endif /* SCENE_MANAGER_HPP */