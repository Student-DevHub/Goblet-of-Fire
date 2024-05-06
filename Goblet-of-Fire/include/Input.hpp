#pragma once
#ifndef INPUT_HPP
#define INPUT_HPP

#include <SFML/Window.hpp>

namespace GobletOfFire {
  namespace Input {
    class InputManager;

    using inputEvent = sf::Event;
  }
}

#include "InputManager.hpp"

#endif // !INPUT_HPP
