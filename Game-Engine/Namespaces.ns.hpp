#pragma once
#ifndef NAMESPACES_HPP
#define NAMESPACES_HPP

#include <mutex>
#include <atomic>

namespace GobletOfFire {
  namespace Core {
    class CoreEngine; //main loop
    class SceneManager; //manages the scenes to be displayed
    class Scene; //the actual scene containing all the objects related to it
  }
  
  namespace TestClasses {
    class TestScene; //just for the sake of test
  }
  
  namespace Graphics {
    class Window; //window class 
    std::mutex window_creation; //will remove soon
  }
}

#endif /* NAMESPACES_HPP */