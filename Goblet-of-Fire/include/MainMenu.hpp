#pragma once
#ifndef MAIN_SCENE_HPP
#define MAIN_SCENE_HPP

#include <cstdint>
#include <memory>

#include <Scene.hpp>
#include <Core.hpp>
#include <Input.hpp>
#include <ObjectComponents.hpp>
#include <Physics.hpp>
#include <Graphics.hpp>

namespace GobletOfFire {
  namespace Scene {
    class MainMenu : public Scene::iScene {
    public:
      MainMenu(std::shared_ptr<Input::InputManager>);
      virtual void create() override;
      virtual void destroy() override {}

      virtual void activate() override;
      virtual void deactivate() override {}

      virtual void updateLogic() override;
      virtual void updateRender() override;

      virtual std::shared_ptr<Graphics::buffer> getBuffer() const override;

    private:
      void processInput();

      std::shared_ptr<Core::ResourceManager<Graphics::texture>> t_resource_allocator_;
      std::shared_ptr<Graphics::buffer> local_buffer_;
      std::shared_ptr<Input::InputManager> input_manager_;

      std::unique_ptr<Graphics::sprite> background_;
      std::unique_ptr<Graphics::sprite> base_;
      std::unique_ptr<Graphics::sprite> options_;

      uint32_t option_;
      const uint32_t total_options_ = 3;
    };
  }
}

#endif // !MAIN_SCENE_HPP
