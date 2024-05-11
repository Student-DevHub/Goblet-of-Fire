#pragma once
#ifndef CHARACTER_B_HPP
#define CHARACTER_B_HPP

#include <functional>
#include <stdexcept>
#include <cstdint>
#include <memory>
#include <map>

#include <Scene.hpp>
#include <Core.hpp>
#include <Input.hpp>
#include <Physics.hpp>
#include <Graphics.hpp>
#include <Design_patterns.hpp>

namespace GobletOfFire {
  namespace Scene {
    class CharacterS_B : public Scene::iScene {
    public:
      CharacterS_B(const std::shared_ptr<Core::SceneManager>&, const std::shared_ptr<Input::InputManager>&);
      virtual void create() override;
      virtual void destroy() override {}

      virtual void activate() override;
      virtual void deactivate() override {}

      virtual void updateLogic() override;
      virtual void updateRender() override;

      virtual std::shared_ptr<Graphics::buffer> getBuffer() const override;

    private:
      void loadTextures();
      void createCallBacks();

      uint32_t processInput();
      void updateOption(uint32_t);

      std::shared_ptr<Core::ResourceManager<Graphics::texture>> t_resource_manager_;
      std::shared_ptr<Graphics::buffer> local_buffer_;
      std::shared_ptr<Input::InputManager> input_manager_;
      std::weak_ptr<Core::SceneManager> scene_manager_;

      std::unique_ptr<Graphics::sprite> background_;
      std::unique_ptr<Graphics::sprite> base_;
      std::unique_ptr<Graphics::sprite> option_;

      uint32_t c_option_;
      const uint32_t kTotalOptions_ = 6;

      std::map<uint32_t, std::shared_ptr<Graphics::texture>> option_textures_;
      std::map<uint32_t, std::function<void()>> callbacks_;
    };
  }
}

#endif // !CHARACTER_B_HPP
