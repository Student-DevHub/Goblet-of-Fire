#pragma once
#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <cstdint>
#include <algorithm>
#include <atomic>

namespace GobletOfFire {
  namespace Core {

    template<typename T>
    class ResourceManager {
    public:
      ResourceManager() : current_id_(0) {}

      std::int64_t add(const std::string& path) {
        auto it = resource_map_.find(path);

        if (it != resource_map_.end()) {
          return it->second.first;
        }

        std::shared_ptr<T> r = std::make_shared<T>();
        if (!r->loadFromFile(path)) {
          return -1;
        }

        resource_map_.emplace(path, std::make_pair(current_id_.fetch_add(1), r));

        return current_id_.load();
      }

      std::shared_ptr<T> get(std::int64_t id) const {
        auto it = std::find_if(resource_map_.begin(), resource_map_.end(),
          [&id](const auto& pair) {
            return pair.second.first == id;
          });

        if (it == resource_map_.end()) {
          return nullptr;
        }

        return it->second.second;
      }

      bool has(std::int64_t id) const {
        auto it = std::find_if(resource_map_.begin(), resource_map_.end(),
          [&id](const auto& pair) {
            return pair.second.first == id;
          });

        return it != resource_map_.end();
      }

    private:
      std::atomic<uint64_t> current_id_;
      std::unordered_map<std::string, std::pair<uint64_t, std::shared_ptr<T>>> resource_map_;
    };
  }
}
#endif // !RESOURCE_MANAGER_HPP
