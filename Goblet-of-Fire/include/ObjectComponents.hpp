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

    class cVelocity;
    class cAcceleration;
    class cColliderBox;
    class cCollider;
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

#endif // !OBJECT_COMPONENT_HPP
