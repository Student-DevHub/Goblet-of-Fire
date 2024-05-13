#include "SceneManager.hpp"


namespace GobletOfFire {
  namespace Core {
    SceneManager::SceneManager(const std::shared_ptr<Core::CoreEngine>& main_engine, 
      const std::shared_ptr<Input::InputManager>& input_handler)  
      : current_scene_(0), main_engine_(main_engine),
        active_buffer_(nullptr), input_handler_(input_handler) {}

    void SceneManager::init() {
      auto main_menu = std::make_shared<Scene::MainMenu>(shared_from_this(), input_handler_, main_engine_);
      auto selection_a = std::make_shared<Scene::CharacterS_A>(shared_from_this(), input_handler_);
      auto selection_b = std::make_shared<Scene::CharacterS_B>(shared_from_this(), input_handler_);
      auto winA = std::make_shared<Scene::EndScreenA>(shared_from_this(), input_handler_);
      auto winB = std::make_shared<Scene::EndScreenB>(shared_from_this(), input_handler_);

      addNewScene(std::make_pair(1, main_menu));
      addNewScene(std::make_pair(2, selection_a));
      addNewScene(std::make_pair(3, selection_b));
      addNewScene(std::make_pair(5, winA));
      addNewScene(std::make_pair(6, winB));
      
      switchTo(1);
    }

    void SceneManager::update() {
      if (current_scene_) {
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
      if (current_scene_) {
        active_buffer_ = scenes_[current_scene_]->getBuffer();
      }
    }

    void SceneManager::addNewScene(const std::pair<uint32_t, std::shared_ptr<Scene::iScene>> &scene) {
      auto it = scenes_.insert(scene);
      if (it.second) {
        it.first->second->create();
      }
    }

    void SceneManager::switchTo(uint32_t id) {
      auto it = scenes_.find(id);

      if (it == scenes_.end() || it->first == current_scene_) {
        throw std::logic_error("Scene either does not exist or is the current scene");
      }
      if (current_scene_) {
        scenes_[current_scene_]->deactivate();
      }
      it->second->activate();

      current_scene_ = it->first;
    }

    void SceneManager::remove(uint32_t id) {
      auto it = scenes_.find(id);

      if (it == scenes_.end() || it->first == current_scene_) {
        return;
      }

      scenes_.erase(it);
    }
    
  }
}