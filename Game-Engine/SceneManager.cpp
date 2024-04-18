#include "SceneManager.hpp"


namespace GobletOfFire {
  namespace Core {
    SceneManager::SceneManager(const std::shared_ptr<Core::CoreEngine> &main_engine)
      : current_scene_(Scenes::kNone), main_engine_(main_engine) {
    }

    void SceneManager::logicLoop() {

      while(main_engine_->shouldStop()) { //first see  if the game is running
        std::unique_lock<std::mutex> lock(update_mut_); //lock to use `std::condition_variable`  
        update_cv_.wait(lock, [this] { return render_status_.load(); }); //if the `render_status_` is false, then wait and release the lock, unlocking `renderLoop()`

        render_status_.store(false); //mark the `render_status_` as false since the logic will be updated in the following statement
        scenes_[current_scene_]->updateLogic();
        logic_status_.store(true); //update the `logic_status_`

        update_cv_.notify_one(); //notify the `renderLoop()`
      }
      
    }

    void SceneManager::renderLoop() { //similar to `logicLoop()`

      while (main_engine_->shouldStop()) {
        std::unique_lock<std::mutex> lock(update_mut_);
        update_cv_.wait(lock, [this] { return logic_status_.load(); });

        logic_status_.store(false);
        scenes_[current_scene_]->updateRender();
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
      active_buffer_ = scenes_[current_scene_]->getBuffer();
      update_buffer_cv_.notify_one();
    }

    void SceneManager::addNewScene(std::pair<Scenes, std::unique_ptr<Core::Scene>> &scene) {
      auto it = scenes_.insert(std::move(scene));
      if (it.second) {
        it.first->second->create();
      }
    }

    void SceneManager::switchTo(SceneManager::Scenes scene) {
      auto it = scenes_.find(scene);

      if (it == scenes_.end() || it->first == current_scene_) {
        throw std::logic_error("Scene either does not exist or is the current scene");
      }

      std::unique_lock<std::mutex> scene_change_;
      scenes_[current_scene_] ->deactivate();
      it->second->activate();

      current_scene_ = it->first;
    }

    void SceneManager::remove(SceneManager::Scenes scene) {
      auto it = scenes_.find(scene);

      if (it == scenes_.end() || it->first == current_scene_) {
        throw std::logic_error("Scene either does not exist or is the current scene");
      }

      scenes_.erase(it);
    }
    
  }
}