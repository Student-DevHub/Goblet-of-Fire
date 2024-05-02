#include "UiElement.hpp"

namespace GobletOfFire {
  namespace UI {
    UIElement::UIElement(const Physics::point2<double_t>& position,
      const Physics::point2<double_t>& size, 
      const std::shared_ptr<Input::InputManager>& i_manager, 
      bool is_visible, bool interactivity)

      : position_(position), size_(size), is_visible_(is_visible), interactivity_(interactivity), 
        input_(i_manager) {
      
      setSize(size);
      setPosition(position);


      ui_buffer_ = std::make_unique<Graphics::buffer>();
      ui_buffer_->create(static_cast<uint32_t>(size.x), static_cast<uint32_t>(size.y));
    }

    void UIElement::setPosition(const Physics::point2<double_t>& position) {
      bool x_condition = position.x < 0 || position.x > Physics::window_dimensions_.x;
      bool y_condition = position.y < 0 || position.y > Physics::window_dimensions_.y;

      if (x_condition || y_condition) {
        throw std::runtime_error("Position is out of bound!");
      }

      position_ = position;
    }

    void UIElement::setSize(const Physics::point2<double_t>& size) {
      if (size.x < 1.0 || size.y < 1.0) {
        throw std::logic_error("Buffer size can't be lower than 1");
      }

      size_ = size;
    }

    void UIElement::setVisibility(bool is_visible) { is_visible_ = is_visible; }

    void UIElement::setInteractivity(bool interactivity){ interactivity_ = interactivity; }

    Physics::point2<double_t> UIElement::getPosition() const { return position_; }
    Physics::point2<double_t> UIElement::getSize() const { return size_; }
    bool UIElement::getVisibility() const { return is_visible_; }
    bool UIElement::getInteractivity() const { return interactivity_; }

    void UIElement::render(Graphics::buffer& destination) {
      if (!(ui_buffer_ && is_visible_)) {
        return;
      }

      sf::Sprite uiSprite(ui_buffer_->getTexture());
      uiSprite.setPosition(static_cast<float_t>(position_.x), static_cast<float_t>(position_.y));
      destination.draw(uiSprite);
    }

    std::weak_ptr<Graphics::texture> UIElement::getTexture() const {
      if (!ui_buffer_) {
        return std::weak_ptr<Graphics::texture>();
      }
      sf::Texture texture = ui_buffer_->getTexture();
      return std::make_shared<sf::Texture>(texture);
    }

  }
}