#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <memory>
#include <mutex>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Namespaces.ns.hpp"

namespace GobletOfFire {
  namespace Graphics {
    class Window : public std::enable_shared_from_this<Window> {
    public:
      Window(const std::string& title = "Window", const sf::Vector2u& size = { 640, 480 });
      Window(const Graphics::Window& other);
      ~Window();

      void beginDraw();
      void draw(sf::Drawable& l_drawable);
      void endDraw();
      void toggleFullScreen();

      bool isCreated() const;
      bool isFullScreen() const;
      sf::Vector2u getWindowSize() const;
      bool getPollEvent(sf::Event& event);

    private:
      void setUp(const std::string& window_title, const sf::Vector2u& window_size, bool is_fullscreen = false);
      void create();
      void destroy();

      sf::RenderWindow window_;
      sf::Vector2u window_size_;
      std::string window_title_;
      bool is_creation_done_;
      bool is_fullscreen_;
    };
  }
}

#endif