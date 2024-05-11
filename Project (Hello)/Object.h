#pragma once

#include "Window.h"
#include "Component.h"
#include "C_Transform.h" // All objects need transform

#include <vector>
#include <memory>
#include <type_traits>

class Object {
public:
    Object();

	// When object created
	void awake();

	// After awake() to initialize variables
	void start();

	void update(float);
	void lateUpdate(float);
	void Draw(Window&);

    template <typename T> std::shared_ptr<T> AddComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        // Check that we don't already have a component of this type.
        for (auto& exisitingComponent : components)
        {
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
                return std::dynamic_pointer_cast<T>(exisitingComponent);
            }
        }

        std::shared_ptr<T> newComponent = std::make_shared<T>(this);
        components.push_back(newComponent);

        return newComponent;
    };

    template <typename T> std::shared_ptr<T> GetComponent()
    {
        // Check that we don't already have a component of this type.
        for (auto& exisitingComponent : components)
        {
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
                return std::dynamic_pointer_cast<T>(exisitingComponent);
            }
        }

        return nullptr;
    };

    bool isQueuedForRemoval();
    void QueuedForRemoval();

    std::shared_ptr<C_Transform> transform;

private:
	std::vector<std::shared_ptr<Component>> components;
    bool queuedForRemoval;
};

