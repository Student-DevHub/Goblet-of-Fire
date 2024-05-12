#pragma once

#include "Window.h"

class Object;

class Component {
public:
	Component(Object *owner) : owner(owner) {}

	virtual void awake() {};
	virtual void start() {};

	virtual void update(float dt) {};
	virtual void lateUpdate(float dt) {};
	virtual void draw(Window& window) {};

protected:
	Object *owner;
};

