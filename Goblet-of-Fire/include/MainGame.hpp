#pragma once
#ifndef MAIN_GAME_HPP
#define MAIN_GAME_HPP

#include <Core.hpp>
#include <Scene.hpp>
#include <Graphics.hpp>
#include <Physics.hpp>
#include <Input.hpp>
#include <ObjectComponents.hpp>
#include <Utilities.hpp>
#include <Design_patterns.hpp>

#include <QuadTree.hpp>

namespace GobletOfFire {
  namespace Scene {
    class MainGame : public Scene::iScene{
    public:
      MainGame(std::shared_ptr<Core::SceneManager>,
        std::shared_ptr<Input::InputManager>);
      ~MainGame() { destroy(); }

      virtual void create() override;
      virtual void destroy() override;

      virtual void activate() override;
      virtual void deactivate() override;

      virtual void updateLogic() override;
      virtual void updateRender() override;

      virtual std::shared_ptr<Graphics::buffer> getBuffer() const override;

    private:
      void checkWinner();

      std::unique_ptr<ObjectComponent::ObjectCollection> object_collection_;
      std::shared_ptr<Graphics::buffer> local_buffer_;
      Utilities::Time::timePoint last_update_;

      std::shared_ptr<Core::ResourceManager<Graphics::texture>> t_resource_manager_;
      std::shared_ptr<Input::InputManager> input_manager_;
      std::weak_ptr<Core::SceneManager> scene_manager_;

      std::shared_ptr<Physics::QuadTree> quadtree_;

      std::shared_ptr<ObjectComponent::cHealth> p1;
      std::shared_ptr<ObjectComponent::cHealth> p2;
    };
  }
}

#endif // !MAIN_GAME_HPP
