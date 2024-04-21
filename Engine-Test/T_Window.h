#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <cstdint>
#include <memory>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace GobletOfFire {
  namespace Physics {
    template <typename T, typename = std::enable_if<std::is_arithmetic<T>::value>>
    using point2 = sf::Vector2<T>;
  }

  namespace Input {
    using inputEvent = sf::Event;
  }
}

namespace GobletOfFire {
  namespace Graphics {
    class Window {
    public:
      Window(const std::string & = "Window", const Physics::point2<std::uint32_t> & = { 640, 480 });
      Window(const Window&) = delete; // Disable copy constructor
      Window& operator=(const Window&) = delete; // Disable copy assignment operator
      ~Window();

      void beginDraw();
      void draw(const sf::Drawable&);
      void endDraw();
      void toggleFullScreen();

      bool isCreated() const;
      bool isFullScreen() const;
      Physics::point2<std::uint32_t> getWindowSize() const;
      bool pollEvent(Input::inputEvent&);

    private:
      void setUp(const std::string&, const Physics::point2<std::uint32_t>&, bool = false);
      void create();
      void destroy();

      std::unique_ptr<sf::RenderWindow> window_;
      Physics::point2<std::uint32_t> window_size_;
      std::string window_title_;
      bool is_creation_done_;
      bool is_fullscreen_;
    };
  }
}

#endif
