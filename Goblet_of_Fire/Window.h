#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GobletOfFire.namespace.h"

namespace GobletOfFire {
  namespace Graphics {
    class Window : public std::enable_shared_from_this<Window> {
    public:
      Window(const std::string& title = "Window", const sf::Vector2u& size = { 640, 480 }) {
        setUp(title, size);
        is_creation_done_ = false;

        create();
      }
      Window(const Graphics::Window& other) {
        setUp(other.window_title_, other.window_size_, other.is_fullscreen_);
        is_creation_done_ = false;

        create();
      }
      ~Window() { destroy(); }

      inline void beginDraw() { window_.clear(sf::Color::Black); }
      inline void draw(sf::Drawable& l_drawable) { window_.draw(l_drawable); }
      inline void endDraw() { window_.display(); }

      inline void toggleFullScreen() {
        std::unique_lock<std::mutex> lock(Graphics::window_creation);
        is_fullscreen_ = !is_fullscreen_;
        destroy();
        create();
      }

      inline bool isCreated() const { return is_creation_done_; }
      inline bool isFullScreen() const { return is_fullscreen_; }
      inline sf::Vector2u getWindowSize() const { return window_size_; }
      inline bool getPollEvent(sf::Event& event) { return window_.pollEvent(event); }

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