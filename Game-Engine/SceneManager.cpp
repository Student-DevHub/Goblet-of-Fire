#include "SceneManager.hpp"


namespace GobletOfFire {
  namespace Core {
    SceneManager::SceneManager(const std::shared_ptr<Core::CoreEngine>& main_engine)
      : current_scene_(Scene::kNone), main_engine_(main_engine),
        active_buffer_(nullptr), render_status_(true), logic_status_(false) {
      auto scene = std::make_pair<Scene, std::shared_ptr<Scenes::Scene>>(Scene::kTest, std::make_shared<Scenes::MyScene>());
      addNewScene(scene);
      switchTo(scene.first);
    }

    void SceneManager::logicLoop() {

      while(!main_engine_->shouldStop()) { 
        std::unique_lock<std::mutex> lock(update_mut_); 
        update_cv_.wait(lock, [this] { return render_status_.load(); }); 

        render_status_.store(false); 
        if(current_scene_ != Scene::kNone) {
          scenes_[current_scene_]->updateLogic();
        }
        logic_status_.store(true); 

        update_cv_.notify_one(); 
      }
      
    }

    void SceneManager::renderLoop() {

      while (!main_engine_->shouldStop()) {
        std::unique_lock<std::mutex> lock(update_mut_);
        update_cv_.wait(lock, [this] { return logic_status_.load(); });

        logic_status_.store(false); 
        if(current_scene_ != Scene::kNone) {
          scenes_[current_scene_]->updateRender();
        }
        render_status_.store(true);

        update_cv_.notify_one();
        updateActiveBuffer();
      }

    }

    std::shared_ptr<sf::RenderTexture> SceneManager::getActiveBuffer() const {
      std::unique_lock<std::mutex> lock(update_buffer_mut_);
      return active_buffer_;
    }

    void SceneManager::updateActiveBuffer() {
      std::unique_lock<std::mutex> lock(update_buffer_mut_);

      if (current_scene_ != Scene::kNone) {
        active_buffer_ = scenes_[current_scene_]->getBuffer();
      }
    }

    void SceneManager::addNewScene(const std::pair<Scene, std::shared_ptr<Scenes::Scene>> &scene) {
      auto it = scenes_.insert(std::move(scene));
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