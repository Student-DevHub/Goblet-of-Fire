#include "Window.hpp"

namespace GobletOfFire {
  namespace Graphics {
    Window::Window(const std::string& title, const sf::Vector2u& size) {
      setUp(title, size);
      is_creation_done_ = false;
      create();
    }

    Window::Window(const Graphics::Window& other) {
      setUp(other.window_title_, other.window_size_, other.is_fullscreen_);
      is_creation_done_ = false;
      create();
    }

    Window::~Window() {
      destroy();
    }

    void Window::beginDraw() {
      window_.clear(sf::Color::Black);
    }

    void Window::draw(sf::Drawable& l_drawable) {
      window_.draw(l_drawable);
    }

    void Window::endDraw() {
      window_.display();
    }

    void Window::toggleFullScreen() {
      std::unique_lock<std::mutex> lock(Graphics::window_creation);
      is_fullscreen_ = !is_fullscreen_;
      destroy();
      create();
    }

    bool Window::isCreated() const {
      return is_creation_done_;
    }

    bool Window::isFullScreen() const {
      return is_fullscreen_;
    }

    sf::Vector2u Window::getWindowSize() const {
      return window_size_;
    }

    bool Window::getPollEvent(sf::Event& event) {
      return window_.waitEvent(event);
    }

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
      is_creation_done_ = false;
      window_.close();
    }
  }
}