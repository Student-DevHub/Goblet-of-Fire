#include "SceneManager.hpp"


namespace GobletOfFire {
  namespace Core {
    SceneManager::SceneManager()
      : current_scene_(0) {
      main_window_ = std::make_shared<Graphics::Window>();
    }

    std::uint32_t SceneManager::addNewScene(std::shared_ptr<Core::Scene> scene) {
      auto has_inserted = scenes_.insert(std::make_pair(++scene_id_tracker_, scene));
      if (has_inserted.second) {
        scene->create();
      }

      return scene_id_tracker_;
    }

    void SceneManager::switchTo(std::uint32_t id) {
      auto it = scenes_.find(id);

      if (it == scenes_.end() || it->first == current_scene_) {
        return;
      }

      scenes_[current_scene_]->deactivate();
      it->second->activate();

      current_scene_ = id;
    }

    void SceneManager::remove(std::uint32_t id) {
      auto it = scenes_.find(id);
    }
    
  }
}