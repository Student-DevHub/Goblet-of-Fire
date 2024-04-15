#pragma once
#ifndef TEST_SCENE_HPP
#define TEST_SCENE_HPP

#include <iostream>
#include <memory>
#include <atomic>

#include <SFML/Graphics.hpp>

#include "Namespaces.ns.hpp"
#include "Scene.hpp"

namespace GobletOfFire {
  namespace TestClasses {
    class TestScene : public Core::Scene {
    public:
      TestScene();

      virtual void create() override;
      virtual void destroy() override;

      virtual void activate() override;
      virtual void deactivate() override;

      virtual void processInput(const sf::Event&) override;

      bool getActivate() const { return activate_; }

    private: 
      std::atomic<bool> activate_;

      std::unique_ptr<sf::Shape> shape_;

    };
  }
}

#endif /* TEST_SCENE_HPP */