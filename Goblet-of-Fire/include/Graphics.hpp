#pragma once
#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace GobletOfFire {
  namespace Graphics {
    //classes in this namespace 

    //namespace variables

    //aliases
    using window = sf::RenderWindow;
    using buffer = sf::RenderTexture;
    using texture = sf::Texture;
    using sprite = sf::Sprite;
    using color = sf::Color;
  }
} 

#endif // !GRAPHICS_HPP
