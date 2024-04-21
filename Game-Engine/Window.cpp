#include "Window.hpp"

namespace GobletOfFire {
  namespace Graphics {
    Window::Window(const std::string& title, const Physics::point2<std::uint32_t>& size)
      : window_(nullptr), window_size_(size), window_title_(title), is_fullscreen_(false) {
      create();
    }

    Window::~Window() {
      destroy();
    }

    void Window::beginDraw() {
      if (window_)
        window_->clear(sf::Color::Black);
    }

    void Window::draw(const sf::Drawable& l_drawable) {
      if (window_)
        window_->draw(l_drawable);
    }

    void Window::endDraw() {
      if (window_)
        window_->display();
    }

    void Window::toggleFullScreen() {
      is_fullscreen_ = !is_fullscreen_;
      destroy();
      create();
    }

    bool Window::isCreated() const {
      return window_ != nullptr && window_->isOpen();
    }

    bool Window::isFullScreen() const {
      return is_fullscreen_;
    }

    Physics::point2<std::uint32_t> Window::getWindowSize() const {
      return window_size_;
    }

    Physics::point2<std::int32_t> Window::getWindowPosition() const {
      return isCreated() ?
        window_->getPosition() : 
        Physics::point2<std::int32_t>(-1, -1);
    }

    bool Window::pollEvent(Input::inputEvent& event) {
      return window_ && window_->pollEvent(event);
    }

    void Window::setUp(const std::string& window_title, const Physics::point2<std::uint32_t>& window_size, bool is_fullscreen) {
      this->window_title_ = window_title;
      this->window_size_ = window_size;
      this->is_fullscreen_ = is_fullscreen;
    }

    void Window::create() {
      if (!window_) {
        auto style = is_fullscreen_ ? sf::Style::Fullscreen : sf::Style::Default;
        window_ = std::make_unique<sf::RenderWindow>(sf::VideoMode(window_size_.x, window_size_.y), window_title_, style);
      }
    }

    void Window::destroy() {
      window_.reset(); // Release the resource
    }
  }
}
