#pragma once
#ifndef DESGIN_PATTERN_HPP
#define DESGIN_PATTERN_HPP

namespace GobletOfFire {
  namespace DesignPatterns {
    template <class T>
    class Singleton;
    template <class SubjectType>
    class Observer;
    template <class SubjectType>
    class Subject;
  }
}
#include "Singleton.hpp"
#include "ObserverPattern.hpp"

#endif // !DESGIN_PATTERN_HPP
