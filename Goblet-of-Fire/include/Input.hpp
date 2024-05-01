#pragma once
#ifndef INPUT_HPP
#define INPUT_HPP

#include <SFML/Window.hpp>

namespace GobletOfFire {
  namespace Input {
    //classes in this namespace
    class InputManager;

    //namespace variables

    //aliases
    using inputEvent = sf::Event;
  }
}

#include "InputManager.hpp"

#endif // !INPUT_HPP
