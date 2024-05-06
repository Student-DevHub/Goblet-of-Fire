#pragma once
#ifndef CORE_HPP
#define CORE_HPP

namespace GobletOfFire {
  namespace Core {
    //classes in this namespace
    class CoreEngine;
    class SceneManager;
    template <typename T>
    class ResourceManager;
    struct ResourcePath;

    //namespace variables
  }
}

#include "CoreEngine.hpp"
#include "SceneManager.hpp"
#include "ResourceManager.hpp"

#endif // !CORE_HPP
