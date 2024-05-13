#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include <ObjectComponents.hpp>
#include <Design_patterns.hpp>
#include <Graphics.hpp>
#include <Core.hpp>

namespace GobletOfFire::ObjectComponent {

  class HealthBar : public DesignPatterns::Observer<cHealth> {
  public:
    HealthBar(uint32_t);
    void create();
    virtual void update(DesignPatterns::Subject<cHealth>* subject) override;
    virtual void subscribe(DesignPatterns::Subject<cHealth>* subject) override;
    void render(Graphics::buffer&) const;

  private:
    uint32_t player_represent_;
    std::unique_ptr<Graphics::sprite> sprite_;
    std::vector<std::shared_ptr<Graphics::texture>> textures_;
    std::shared_ptr<Core::ResourceManager<Graphics::texture>> t_manager_;
  };

  class HealthBarObjectAdapter : public iObject {
  public:
    HealthBarObjectAdapter(std::shared_ptr<HealthBar>);

    virtual void create() override;
    virtual void destroy() override;

    virtual void activate() override;
    virtual void deActivate() override;

    virtual void update(const iComponent::Type, const Utilities::Time::duration) override;
    virtual void render(Graphics::buffer&) const override;

    virtual void addComponent(const iComponent::Type, const std::shared_ptr<iComponent>&) override;
    virtual void removeComponent(const iComponent::Type) override;
    virtual std::shared_ptr<iComponent> getComponent(const iComponent::Type) const override;

    virtual bool isDestroyed() const override;

  private:
    std::shared_ptr<HealthBar> bar_;
  };
}