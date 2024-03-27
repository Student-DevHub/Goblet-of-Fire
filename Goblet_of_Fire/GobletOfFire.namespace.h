#pragma once
#ifndef NAMESPACES_H
#define NAMESPACES_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace GobletOfFire {
  bool gameStatus;

  namespace CoreGame {
    class GobletofFire;
    class GameState;
  }

  namespace Graphics {
    std::mutex window_creation;
    
    class Window;
  }

  namespace tests {
    class TestingState;
  }
}

#endif