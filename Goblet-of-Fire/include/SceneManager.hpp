#pragma once
#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <cstdint>
#include <memory>
#include <map>

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

      void init();
      void update();

      std::shared_ptr<Graphics::buffer> getActiveBuffer() const;
      void updateActiveBuffer();

      void addNewScene(const std::pair<uint32_t, std::shared_ptr<Scene::iScene>>&);
      void switchTo(uint32_t);
      void remove(uint32_t);

    private:
      std::weak_ptr<Core::CoreEngine> main_engine_;
      std::shared_ptr<Input::InputManager> input_handler_;

      std::map<uint32_t,
        std::shared_ptr<Scene::iScene>> scenes_;  

      uint32_t current_scene_;

      std::shared_ptr<Graphics::buffer> active_buffer_;
    };

  }
}

#endif /* SCENE_MANAGER_HPP */