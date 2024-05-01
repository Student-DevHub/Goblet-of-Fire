#pragma once
#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <cstdint>

#include <SFML/System.hpp>

namespace GobletOfFire {
  namespace Physics {
    template<typename T>
    using point2 = sf::Vector2<T>; //custom name for vector2

    extern point2<uint32_t> window_dimensions_;
  }
}

#endif // !PHYSICS_HPP
