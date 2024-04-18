#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "Namespaces.ns.hpp"
#include "SceneManager.hpp"

namespace GobletOfFire {
  namespace Core {
    class Scene : public std::enable_shared_from_this<Core::Scene> {
    public:
      virtual void create() = 0;
      virtual void destroy() = 0;

      virtual void activate() = 0;
      virtual void deactivate() = 0;

      virtual void updateLogic() = 0;
      virtual void updateRender() = 0;

      inline virtual std::shared_ptr<sf::RenderTexture> getBuffer() const = 0;
    };
  }
}

#endif /* SCENE_HPP */