#pragma once
#ifndef OBJECT_COMPONENT_HPP
#define OBJECT_COMPONENT_HPP

namespace GobletOfFire {
  namespace ObjectComponent {
    class iObject;
    class iComponent;
    class Object;
    class ObjectCollection;

    class cTransform;
    class cSprite;
    class cAnimation;
    class cKeyboardMovement;
    class cPhysics;
    class cHealth;
    class cCollision;
  }
}

#include "iComponent.hpp"
#include "iObject.hpp"
#include "Object.hpp"
#include "ObjectCollection.hpp"
#include "cTransform.hpp"
#include "cSprite.hpp"
#include "cAnimation.hpp"
#include "cKeyboardMovement.hpp"
#include "cPhysics.hpp"
#include "cCollision.hpp"
#include "cHealth.hpp"
#include "HealthBar.hpp"

#endif // !OBJECT_COMPONENT_HPP
