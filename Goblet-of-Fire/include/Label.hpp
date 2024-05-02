#pragma once
#ifndef LABEL_HPP
#define LABEL_HPP

#include <memory>
#include <string>

#include <Core.hpp>
#include <Graphics.hpp>
#include <Ui_elements.hpp>
#include <Design_patterns.hpp>

/*
UIElement(const Physics::point2<double_t>&,
    const Physics::point2<double_t>&,
    const std::shared_ptr<Input::InputManager>&,
    bool = true, bool = false
    );
*/

namespace GobletOfFire {
  namespace UI {
    
    class Label : public UI::UIElement,
                  public DesignPatterns::Observer<Button> {
    public:
      
      virtual void update() override; //override update() from UI::UIElement
      virtual void update(const DesignPatterns::Subject<Button>&) override; //override update() from DesignPatterns::Observer<T>

      
    private:
      std::shared_ptr<Graphics::texture> t_background_;
      std::unique_ptr<Graphics::sprite> s_background_;

      std::string text_field_;
      std::unique_ptr<UI::text> text_;
      std::pair<Graphics::color, Graphics::color> text_color_; //normal and hover
      bool is_transparent_;

    };

  }
}

#endif // !LABEL_HPP
