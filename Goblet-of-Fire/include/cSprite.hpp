#pragma once
#ifndef C_SPRITE_HPP
#define C_SPRITE_HPP

#include <cstdint>
#include <memory>

#include <ObjectComponents.hpp>
#include <Graphics.hpp>
#include <Physics.hpp>
#include <Core.hpp>

namespace GobletOfFire::ObjectComponent {
  class cSprite : public iComponent {
  public:
    using spriteRect = sf::IntRect;

    cSprite(uint32_t, std::shared_ptr<iObject>);

    virtual void create() override;
    virtual void destroy() override;

    virtual void activate() override;
    virtual void deActivate() override;

    virtual void update(const Utilities::Time::duration) override;
    virtual void render(Graphics::buffer&) override;

    void setTextureRect(Physics::point2<int32_t> , Physics::point2<int32_t>);
    void setScale(float, float);

  private:
    uint32_t sprite_id_;
    std::weak_ptr<iObject> owner_;
    std::weak_ptr<cTransform> transform_;

    std::unique_ptr<Graphics::sprite> sprite_;
    std::shared_ptr<Graphics::texture> texture_;
    
    std::shared_ptr<Core::ResourceManager<Graphics::texture>> t_resource_manager_;
  };
}

#endif // !C_SPRITE_HPP
