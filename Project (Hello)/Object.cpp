#include "Object.h"

Object::Object() : queuedForRemoval(false)
{
	transform = AddComponent<C_Transform>();
}

/* Looped in reverse order for components can get removed runtime */

void Object::awake() {
	for (int i = components.size()-1; i >= 0; i--)
		components[i]->awake();
}

void Object::start() {
	for (int i = components.size()-1; i >= 0; i--)
		components[i]->start();
}

void Object::update(float dt) {
	for (int i = components.size()-1; i >= 0; i--)
		components[i]->update(dt);
}

void Object::lateUpdate(float dt) {
	for (int i = components.size()-1; i >= 0; i--)
		components[i]->lateUpdate(dt);
}

void Object::Draw(Window& window) {
	for (int i = components.size()-1; i >= 0; i--)
		components[i]->draw(window);
}

bool Object::isQueuedForRemoval()
{
	return queuedForRemoval;
}

void Object::QueuedForRemoval() {
	queuedForRemoval = true;
}
