#pragma once
#ifndef NAMESPACES_H
#define NAMESPACES_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <concurrent_queue.h>
#include <stack>
#include <concurrent_vector.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace GobletOfFire {
  extern bool gameStatus;

  namespace CoreGame {
    class GobletofFire;
    class MagicScreen;
  }

  namespace Graphics {
    extern std::mutex window_creation;
    
    class Window;
  }

  namespace Input {
    class Wizard;
    class Spell;
  }

  namespace Utils {

  }

  namespace tests {
    class TestingState;
  }
}

#endif