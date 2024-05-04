#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>

#include <Graphics.hpp>

namespace GobletOfFire {
  namespace Scene {
    class iScene : public std::enable_shared_from_this<iScene> {
    public:
      virtual ~iScene() {}

      virtual void create() = 0;
      virtual void destroy() = 0;

      virtual void activate() = 0;
      virtual void deactivate() = 0;

      virtual void updateLogic() = 0;
      virtual void updateRender() = 0;

      virtual std::shared_ptr<Graphics::buffer> getBuffer() const = 0;
    };
  }
}

#endif /* SCENE_HPP */