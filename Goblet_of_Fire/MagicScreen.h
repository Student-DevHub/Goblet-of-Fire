#pragma once
#ifndef MAGIC_SCREEN
#define MAGIC_SCREEN

#include <string>
#include <memory>
#include <iostream>
#include <thread>
#include "GobletOfFire.namespace.h"
#include "GobletOfFire.h"
#include "Window.h"

namespace GobletOfFire {
  namespace CoreGame {
    class MagicScreen {
    public:
      virtual void handleInput() = 0;
      virtual void end() = 0;
      virtual void renderEverything() = 0;
    };
  }
}
#endif
