#pragma once

#include <memory>

#include <ObjectComponents.hpp>
#include <Design_patterns.hpp>

namespace GobletOfFire::ObjectComponent {

  class cHealth : public iComponent, 
    public DesignPatterns::Subject<cHealth> {
  public:
    virtual void create() override;
    virtual void destroy() override;

    virtual void activate() override;
    virtual void deActivate() override;

    virtual void update(const Utilities::Time::duration) override;
    virtual void render(Graphics::buffer&) override;

    double getHealth() const;
    void takeDamage(double);
    void heal(double);
    
  private:
    double health_;
    static double kMaxHealth_;
  };

}