#pragma once
#ifndef NAMESPACES_HPP
#define NAMESPACES_HPP

#include <type_traits>
#include <functional>
#include <unordered_map>

#include <SFML/System.hpp>

namespace GobletOfFire {
  namespace Core {
    class CoreEngine; //main loop
    class SceneManager; //manages the scenes to be displayed
    class ThreadPool; //main thread pool for engine
  }
  
  namespace Graphics {
    class Window; //window class 
  }

  namespace Physics {
    template<typename T>
    using point2 = sf::Vector2<T>;
  }

  namespace Input {
    class InputManager;
  }

  namespace Scenes {
    class Scene; //the actual scene containing all the objects related to it

    class WorkersPool;
  }
  
  namespace TestClasses {
    class TestScene; //just for the sake of test
  }

  namespace Utilities {
    class Time;
  }

  namespace Template {
    struct EnumHashFunc {
      template <typename T>
      std::size_t operator() (T t) {
        return static_cast<std::size_t>(t);
      }
    };

    template <typename Key>
    using HashType = typename std::conditional<std::is_enum_v<Key>, EnumHashFunc, std::hash<Key>>::type;

    template <class Key, typename T>
    using enum_unordered_map = std::unordered_map<Key, T, HashType<Key>>;
  }
  
}

#endif /* NAMESPACES_HPP */