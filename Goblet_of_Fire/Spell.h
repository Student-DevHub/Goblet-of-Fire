#pragma once
#ifndef SPELL_INTERFACE
#define SPELL_INTERFACE

#include "GobletOfFire.namespace.h"

namespace GobletOfFire {
  namespace Input {
    class Spell {
    public:
      virtual void cast() = 0;
    };
  }
}

#endif