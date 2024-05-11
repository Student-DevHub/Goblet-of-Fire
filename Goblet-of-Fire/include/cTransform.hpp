#pragma once
#ifndef C_TRANSFORM_HPP
#define C_TRANSFORM_HPP

#include <ObjectComponents.hpp>
#include <Utilities.hpp>
#include <Graphics.hpp>
#include <Physics.hpp>

namespace GobletOfFire::ObjectComponent {
  class cTransform : public iComponent {
  public:
    cTransform(uint32_t, uint32_t);

    virtual void create() override;
    virtual void destroy() override;

    virtual void activate() override;
    virtual void deActivate() override;

    virtual void update(const Utilities::Time::duration) override;
    virtual void render(Graphics::buffer&) override;

    void setPosition(uint32_t, uint32_t);
    void setPosition(Physics::point2<uint32_t>);

    Physics::point2<uint32_t> getPoint() const;

  private:
    Physics::point2<uint32_t> point_;
  };
}

#endif // !C_TRANSFORM_HPP
