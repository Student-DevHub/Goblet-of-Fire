#include "SceneManager.hpp"


namespace GobletOfFire {
  namespace Core {
    SceneManager::SceneManager(const std::shared_ptr<Core::CoreEngine>& main_engine, const std::shared_ptr<Input::InputManager>& input_handler)
      
      : current_scene_(Scene::kNone), main_engine_(main_engine),
        active_buffer_(nullptr), input_handler_(input_handler) {
      
      auto test_scene = std::make_shared<Scenes::MyScene>();
      auto scene = std::make_pair<Scene, std::shared_ptr<Scenes::Scene>>(Scene::kTest, test_scene);
      addNewScene(scene);
      switchTo(scene.first);

    }

    void SceneManager::update() {
      if (current_scene_ != Scene::kNone) {
        auto& curr = scenes_[current_scene_];
        curr->updateLogic();
        curr->updateRender();
        this->updateActiveBuffer();
      }
    }

    std::shared_ptr<sf::RenderTexture> SceneManager::getActiveBuffer() const {
      return active_buffer_;
    }

    void SceneManager::updateActiveBuffer() {
      if (current_scene_ != Scene::kNone) {
        active_buffer_ = scenes_[current_scene_]->getBuffer();
      }
    }

    void SceneManager::addNewScene(const std::pair<Scene, std::shared_ptr<Scenes::Scene>> &scene) {
      auto it = scenes_.insert(scene);
      if (it.second) {
        it.first->second->create();
      }
    }

    void SceneManager::switchTo(SceneManager::Scene scene) {
      auto it = scenes_.find(scene);

      if (it == scenes_.end() || it->first == current_scene_) {
        throw std::logic_error("Scene either does not exist or is the current scene");
      }

      std::unique_lock<std::mutex> scene_change_;
      if (current_scene_ != Scene::kNone) {
        scenes_[current_scene_]->deactivate();
      }
      it->second->activate();

      current_scene_ = it->first;
    }

    void SceneManager::remove(SceneManager::Scene scene) {
      auto it = scenes_.find(scene);

      if (it == scenes_.end() || it->first == current_scene_) {
        throw std::logic_error("Scene either does not exist or is the current scene");
      }

      scenes_.erase(it);
    }
    
  }
}