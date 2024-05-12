#pragma once

/*
 * Abstract Class for Scenes
 */


#include "Window.h"

class Scene {
public:

    /* Necessary to Override */
    virtual void onCreate() = 0; // When screen created
    virtual void onDestroy() = 0; // When scene destroyed (if destroyed)

    /* Override as Necessary */
    virtual void onActivate() {}; // When transitioned into
    virtual void onDeactivate() {}; // When transitioned out of
    
    virtual void ProcessInput() {};
    virtual void Update(float deltaTime) {};
    virtual void LateUpdate(float deltaTime) {};
    virtual void Draw(Window& window) {};

};
