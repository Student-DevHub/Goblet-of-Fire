#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>

#include <SFML/Graphics.hpp>

namespace GobletOfFire {
  namespace Scene {
    class iScene : public std::enable_shared_from_this<iScene> {
    public:
      virtual void create() = 0;
      virtual void destroy() = 0;

      virtual void activate() = 0;
      virtual void deactivate() = 0;

      virtual void updateLogic() = 0;
      virtual void updateRender() = 0;

      virtual std::shared_ptr<sf::RenderTexture> getBuffer() const = 0;
    };
  }
}

#endif /* SCENE_HPP */