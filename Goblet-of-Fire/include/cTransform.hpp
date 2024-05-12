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
    cTransform(float, float);

    virtual void create() override;
    virtual void destroy() override;

    virtual void activate() override;
    virtual void deActivate() override;

    virtual void update(const Utilities::Time::duration) override;
    virtual void render(Graphics::buffer&) override;

    void setPosition(float, float);
    void setPosition(Physics::point2<float>);

    Physics::point2<float> getPoint() const;

  private:
    Physics::point2<float> point_;
  };
}

#endif // !C_TRANSFORM_HPP
