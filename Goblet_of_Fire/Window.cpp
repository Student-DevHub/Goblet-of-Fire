#include "Window.h"

namespace GobletOfFire {
  void Window::setUp(const std::string& window_title, const sf::Vector2u& window_size, bool is_fullscreen) {
    this->window_title_ = window_title;
    this->window_size_ = window_size;
    this->is_fullscreen_ = is_fullscreen;
  }

  void Window::create() {
    if (is_creation_done_)
      return;

    auto fullScreen = is_fullscreen_ ? sf::Style::Fullscreen : sf::Style::Default;
    window_.create(sf::VideoMode(window_size_.x, window_size_.y), window_title_, fullScreen);
    is_creation_done_ = true;
  }

  void Window::destroy() {
    window_.close();
    is_creation_done_ = false;
  }
}