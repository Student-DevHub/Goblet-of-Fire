#include "SceneStateMachine.h"

SceneStateMachine::SceneStateMachine() 
	: scenes(0), currentScene(0), currentSceneID(0) {
}

void SceneStateMachine::ProcessInput() {
	if (currentScene)
		currentScene->ProcessInput();
}

void SceneStateMachine::Update(float deltaTime) {
	if (currentScene)
		currentScene->Update(deltaTime);
}

void SceneStateMachine::LateUpdate(float deltaTime) {
	if (currentScene)
		currentScene->LateUpdate(deltaTime);
}

void SceneStateMachine::Draw(Window& window) {
	if (currentScene)
		currentScene->Draw(window);
}

unsigned int SceneStateMachine::add(std::shared_ptr<Scene> scene) {
	auto inserted = scenes.insert(std::make_pair(currentSceneID, scene));
	++currentSceneID;
	inserted.first->second->onCreate();

	return currentSceneID - 1;
}

void SceneStateMachine::switchTo(unsigned int ID) {
	auto it = scenes.find(ID);
	if (it != scenes.end())
	{
		// If any scene in running
		if (currentScene)
			currentScene->onDeactivate();

		currentScene = it->second;

		currentScene->onActivate();
	}
}

void SceneStateMachine::remove(unsigned int ID) {
	auto it = scenes.find(ID);
	if (it != scenes.end())
	{
		// If currentScene is the one being removed
		if (currentScene == it->second)
			currentScene = NULL;

		it->second->onDestroy();

		scenes.erase(it);
	}
}
