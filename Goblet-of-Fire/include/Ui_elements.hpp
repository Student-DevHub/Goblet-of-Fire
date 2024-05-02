#pragma once
#ifndef UI_ELEMENTS_HPP
#define UI_ELEMENTS_HPP

#include <SFML/Graphics.hpp>

namespace GobletOfFire {
  namespace UI {
    class UIElement;
    
    class Button;
    class Label;
    class Icon;
    class TextEntry;
    class ProgressBar;

    class ContainerBox;

    class ProgressBar;

    using font = sf::Font;
    using text = sf::Text;
  }
}

#include "UiElement.hpp"
#include "Label.hpp"

#endif // !UI_ELEMENTS_HPP
