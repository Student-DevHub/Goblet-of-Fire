#pragma once
#ifndef C_PHYSICS_HPP
#define C_PHYSICS_HPP

#include <memory>

#include <ObjectComponents.hpp>
#include <Physics.hpp>
#include <Graphics.hpp>

namespace GobletOfFire::ObjectComponent {

  class cPhysics : public iComponent {
  public:
    cPhysics(std::shared_ptr<iObject>, Physics::point2<float>, float, float);

    virtual void create() override;
    virtual void destroy() override {}

    virtual void activate() override {}
    virtual void deActivate() override {}

    virtual void update(const Utilities::Time::duration) override;
    virtual void render(Graphics::buffer&) override {}

    void setVelocity(Physics::point2<float>);
    Physics::point2<float> getVelocity() const;
    Physics::point2<float> getMaxVelocity() const;

    void setAcceleration(Physics::point2<float>);
    Physics::point2<float> getAcceleration() const;

    float getMass() const;
    void setGravity(float);
    float getGravity() const;

  private:
    std::weak_ptr<iObject> owner_;
    std::weak_ptr<cTransform> transform_;

    Physics::point2<float> velocity_;
    Physics::point2<float> acceleration_;

    float mass_;
    float gravity_;

    Physics::point2<float> max_velocity_;
  };
}


#endif // !C_PHYSICS_HPP