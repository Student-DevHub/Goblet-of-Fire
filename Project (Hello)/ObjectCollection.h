#pragma once

#include <memory>
#include <vector>

#include "Object.h"

class ObjectCollection {
public:
	void Add(std::shared_ptr<Object> object);

	void update(float dt);
	void lateUpdate(float dt);
	void draw(Window& window);

	void processNewObjects();
	void processRemovals();

private:
	std::vector<std::shared_ptr<Object>> objects;
	std::vector<std::shared_ptr<Object>> newObjects;
};

