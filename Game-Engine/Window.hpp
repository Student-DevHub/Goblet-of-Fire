#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <cstdint>
#include <memory>
#include <mutex>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Physics.hpp"
#include "Input.hpp"

namespace GobletOfFire {
  namespace Graphics {
    class Window {
    public:
      Window(const std::string & = "Window", const Physics::point2<std::uint32_t> & = { 640, 480 });
      Window(const Window&) = delete; 
      Window& operator=(const Window&) = delete; 
      ~Window();

      void beginDraw();
      void draw(const sf::Drawable&);
      void endDraw();
      void toggleFullScreen();

      bool isCreated() const;
      bool isFullScreen() const;
      Physics::point2<std::uint32_t> getWindowSize() const;
      Physics::point2<std::int32_t> getWindowPosition() const; 
      bool pollEvent(Input::inputEvent&);

    private:
      void setUp(const std::string&, const Physics::point2<std::uint32_t>&, bool = false);
      void create();
      void destroy();

      std::unique_ptr<sf::RenderWindow> window_;
      Physics::point2<std::uint32_t> window_size_;
      std::string window_title_;
      bool is_fullscreen_;
    };
  }
}

#endif