#pragma once
#ifndef MAIN_GAME_HPP
#define MAIN_GAME_HPP

#include <Scene.hpp>
#include <Graphics.hpp>
#include <Physics.hpp>
#include <Input.hpp>
#include <ObjectComponents.hpp>
#include <Utilities.hpp>
#include <Design_patterns.hpp>

namespace GobletOfFire {
  namespace Scene {
    class MainGame : public Scene::iScene{
    public:
      MainGame() = default;
      ~MainGame() { destroy(); }

      virtual void create() override;
      virtual void destroy() override;

      virtual void updateLogic() override;
      virtual void updateRender() override;

      virtual std::shared_ptr<Graphics::buffer> getBuffer() const override;

    private:
      std::unique_ptr<ObjectComponent::ObjectCollection> object_collection_;

      std::shared_ptr<Core::ResourceManager<Graphics::texture>> t_resource_manager_;
      std::unique_ptr<Graphics::buffer> local_buffer_;
      std::shared_ptr<Input::InputManager> input_manager_;
      std::weak_ptr<Core::SceneManager> scene_manager_;

    };
  }
}

#endif // !MAIN_GAME_HPP
