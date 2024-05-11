#include "ObjectCollection.h"

void ObjectCollection::Add(std::shared_ptr<Object> object) {
	newObjects.push_back(object);
}

void ObjectCollection::update(float dt) {
	for (auto& o : objects) {
		o->update(dt);
	}
}

void ObjectCollection::lateUpdate(float dt) {
	for (auto& o : objects) {
		o->lateUpdate(dt);
	}
}

void ObjectCollection::draw(Window& window) {
	for (auto& o : objects) {
		o->Draw(window);
	}
}

void ObjectCollection::processNewObjects() {
	if (newObjects.size() > 0) {
		for (const auto& o : newObjects) {
			o->awake();
		}

		for (const auto& o : newObjects) {
			o->start();
		}

		objects.assign(newObjects.begin(), newObjects.end());
		newObjects.clear();
	}
}

void ObjectCollection::processRemovals() {
	auto objIterator = objects.begin();
	while (objIterator != objects.end())
	{
		auto obj = *objIterator;

		if (obj->isQueuedForRemoval()) {
			objIterator = objects.erase(objIterator);
		}
		else {
			++objIterator;
		}
	}
}
