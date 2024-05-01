#pragma once
#ifndef UI_ELEMENT_HPP
#define UI_ELEMENT_HPP

#include <cstdint>
#include <memory>

#include <Ui_Elements.hpp>
#include <Graphics.hpp>
#include <Physics.hpp>
#include <Input.hpp>

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

#endif // !UI_ELEMENT_HPP
