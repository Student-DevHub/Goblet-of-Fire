#pragma once
#ifndef NAMESPACES_HPP
#define NAMESPACES_HPP

#include <SFML/System.hpp>

namespace GobletOfFire {
  

  



  namespace Core {
    class CoreEngine; //main loop
    class SceneManager; //manages the scenes to be displayed
    class ThreadPool;
  }
  
  namespace Graphics {
    class Window; //window class 
  }

  namespace Physics {
    template<typename T>
    using point_2 = sf::Vector2<T>;
  }

  namespace Input {
    class InputManager;
  }

  namespace Scene {
    class Scene; //the actual scene containing all the objects related to it

    class WorkersPool;
  }
  
  namespace TestClasses {
    class TestScene; //just for the sake of test
  }

  namespace Utilities {
    class Time;
  }
  
}

#endif /* NAMESPACES_HPP */