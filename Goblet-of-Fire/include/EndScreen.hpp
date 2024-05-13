#pragma once

#include <Scene.hpp>

namespace GobletOfFire::Scene {
  class EndScreenA : public iScene {
  public:
    EndScreenA(const std::shared_ptr<Core::SceneManager>&, const std::shared_ptr<Input::InputManager>&);

    virtual void create() override;
    virtual void destroy() override;

    virtual void activate() override;
    virtual void deactivate() override;

    virtual void updateLogic() override;
    virtual void updateRender() override;

    virtual std::shared_ptr<Graphics::buffer> getBuffer() const override;

  private:
    const Utilities::Time::duration time_to_show_;

    std::shared_ptr<Core::ResourceManager<Graphics::texture>> t_resource_manager_;
    std::shared_ptr<Graphics::buffer> local_buffer_;
    std::shared_ptr<Input::InputManager> input_manager_;
    std::weak_ptr<Core::SceneManager> scene_manager_;

    std::unique_ptr<Graphics::sprite> background_;
    std::unique_ptr<Graphics::sprite> foreground_;

    Utilities::Time::timePoint start_;
  };

  class EndScreenB : public iScene {
  public:
    EndScreenB(const std::shared_ptr<Core::SceneManager>&, const std::shared_ptr<Input::InputManager>&);

    virtual void create() override;
    virtual void destroy() override;

    virtual void activate() override;
    virtual void deactivate() override;

    virtual void updateLogic() override;
    virtual void updateRender() override;

    virtual std::shared_ptr<Graphics::buffer> getBuffer() const override;

  private:
    const Utilities::Time::duration time_to_show_;

    std::shared_ptr<Core::ResourceManager<Graphics::texture>> t_resource_manager_;
    std::shared_ptr<Graphics::buffer> local_buffer_;
    std::shared_ptr<Input::InputManager> input_manager_;
    std::weak_ptr<Core::SceneManager> scene_manager_;

    std::unique_ptr<Graphics::sprite> background_;
    std::unique_ptr<Graphics::sprite> foreground_;

    Utilities::Time::timePoint start_;
  };

}