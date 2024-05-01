#pragma once
#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <utility>
#include <string>
#include <memory>
#include <cstdint>
#include <algorithm>
#include <stdexcept>

#include <Design_patterns.hpp>

namespace GobletOfFire {
  namespace Core {
    struct ResourcePath {
      static std::string resources_directory_;
      static std::map<uint64_t, std::string> paths_;
    };

    template<typename T>
    class ResourceManager : public DesignPatterns::Singleton<ResourceManager<T>> {
    public:
      friend class DesignPatterns::Singleton<ResourceManager<T>>;

      std::shared_ptr<T> load(uint64_t id) {
        
        auto ptr = get(id);
        if (ptr) {
          return ptr;
        }

        auto it = ResourcePath::paths_.find(id);
        if (it == ResourcePath::paths_.end()) {
          throw std::runtime_error("The resource id" + std::to_string(id) + " is not mapped!");
        }

        ptr = std::make_shared<T>();
        std::string path = ResourcePath::resources_directory_ + it->second;
        if (!ptr->loadFromFile(path)) {
          throw std::logic_error("The resource id" + std::to_string(id) + " has wrong path mapped!");
        }

        this->resource_map_.emplace(std::make_pair(id, ptr));
        return ptr;
      }

      std::shared_ptr<T> get(uint64_t id) const {
        auto it = resource_map_.find(id);

        if (it == resource_map_.end()) {
          return nullptr;
        }

        return it->second;
      }

      bool has(uint64_t id) const {
        auto ptr = get(id);

        return ptr != nullptr;
      }

      void remove(uint64_t id) {
        if (!has(id))
          return;
        auto it = resource_map_.find(id);
        resource_map_.erase(it);
      }

      virtual ~ResourceManager() {}

    private:
      ResourceManager() {}

      std::map<uint64_t, std::shared_ptr<T>> resource_map_;
    };
  }
}
#endif // !RESOURCE_MANAGER_HPP
