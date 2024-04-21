#pragma once
#ifndef TEST_SCENE_HPP
#define TEST_SCENE_HPP
#define DIR "../Game-Engine/"

#include <memory>

#include <SFML/Graphics.hpp> 

#include "Namespaces.ns.hpp"
#include "SceneManager.hpp"
#include "Scene.hpp"
#include "InputManager.hpp"
#include "Time.hpp"

class TestScene : public GobletOfFire::Scenes::Scene  {
public:
  TestScene() : buffer_(nullptr), shape_ptr_(nullptr) {}

  virtual void create() override {}
  virtual void destroy() override {}

  virtual void activate() override {}
  virtual void deactivate() override {}

  virtual void updateLogic() override {}
  virtual void updateRender() override {}

  inline virtual std::shared_ptr<sf::RenderTexture> getBuffer() const override { return nullptr; }

private:
  std::shared_ptr<sf::RenderTexture> buffer_;
  std::shared_ptr<sf::Shape> shape_ptr_;
};


#endif // !TEST_SCENE_HPP
