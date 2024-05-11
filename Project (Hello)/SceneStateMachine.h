#pragma once

#include <memory>
#include <unordered_map>

#include "Scene.h"
#include "Window.h"

class SceneStateMachine{
public:
	SceneStateMachine();

    /* Pass Through Methods - Call Current Scenes methods */
    void ProcessInput();
    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Draw(Window& window);

    /* Each scene will have a unique ID */
    unsigned int add(std::shared_ptr<Scene> scene);
    void switchTo(unsigned int ID); // Call destory() of current, activate() of new
    void remove(unsigned int ID);

private:
    std::unordered_map< unsigned int, std::shared_ptr<Scene> > scenes;
    std::shared_ptr<Scene> currentScene;
    unsigned int currentSceneID; /*to be inserted ki ID he*/
};

