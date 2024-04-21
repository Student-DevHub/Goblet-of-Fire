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

#include "Namespaces.ns.hpp"

namespace GobletOfFire {
  namespace Graphics {
    class Window : public std::enable_shared_from_this<Window> {
    public:
      using point2 = Physics::point2<std::uint32_t>;
      Window(const std::string& title = "Window", const point2& size = { 640, 480 });
      Window(const Graphics::Window&);
      ~Window();

      void beginDraw();
      void draw(const sf::Drawable&);
      void endDraw();
      void toggleFullScreen();

      bool isCreated() const;
      bool isFullScreen() const;
      sf::Vector2u getWindowSize() const;
      bool pollEvent(sf::Event&);

      const sf::RenderWindow& getRenderWindow() const;

    private:
      void setUp(const std::string& window_title, const sf::Vector2u& window_size, bool is_fullscreen = false);
      void create();
      void destroy();

      sf::RenderWindow window_;
      point2 window_size_;
      std::string window_title_;
      bool is_creation_done_;
      bool is_fullscreen_;
    };
  }
}

#endif