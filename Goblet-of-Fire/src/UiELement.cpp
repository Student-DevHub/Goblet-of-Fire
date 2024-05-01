#include "UiElement.hpp"

/*
class GobletOfFire::UI::UIElement {
public:
  UIElement(const Physics::point2<double_t>&,
    const Physics::point2<double_t>&, bool, bool,
    const std::shared_ptr<Input::InputManager>&);

  void setPosition(const Physics::point2<double_t>&);
  void setSize(const Physics::point2<double_t>&);
  void setVisibility(bool);
  void setInteractivity(bool);

  Physics::point2<double_t> getPosition() const;
  Physics::point2<double_t> getSize() const;
  bool getVisibility() const;
  bool getInteractivity() const;

  virtual void render(Graphics::buffer&);
  virtual std::weak_ptr<Graphics::texture> getTexture();
  virtual void update() = 0;

private:
  Physics::point2<double_t> position_;
  Physics::point2<double_t> size_;
  bool is_visible_;
  bool interactivity_;

  std::unique_ptr<Graphics::buffer> ui_buffer_;
  std::shared_ptr<Input::InputManager> input_;
};
*/

namespace GobletOfFire {
  namespace UI {
    UIElement::UIElement(const Physics::point2<double_t>& position,
      const Physics::point2<double_t>& size, bool is_visible, bool interactivity,
      const std::shared_ptr<Input::InputManager>& i_manager)
      : position_(position), size_(size), is_visible_(is_visible), interactivity_(interactivity), 
        input_(i_manager) {
      if (size.x < 1.0 || size.y < 1.0) {
        throw std::logic_error("Buffer size can't be lower than 1");
      }

      ui_buffer_ = std::make_unique<Graphics::buffer>();
      ui_buffer_->create(size.x, size.y);
    }

    void 

  }
}