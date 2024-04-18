#pragma once
#ifndef NAMESPACES_HPP
#define NAMESPACES_HPP

#include <mutex>
#include <atomic>

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

  }

  namespace Input {

  }

  namespace Scene {
    class Scene; //the actual scene containing all the objects related to it

    class WorkersPool;
  }
  
  namespace TestClasses {
    class TestScene; //just for the sake of test
  }

  using clock = std::chrono::steady_clock;
  using timePoint = std::chrono::time_point<clock>;
  using duration = std::chrono::milliseconds;
  namespace Utilities {
    class TimeManager;
  }
  
}

#endif /* NAMESPACES_HPP */