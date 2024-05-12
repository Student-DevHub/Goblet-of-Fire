#pragma once

#include <map>
#include <memory>
#include <string>

template <typename T> class ResourceAllocator {
public:
	int Add(const std::string& filepath) {
		auto it = resources.find(filepath);

		if (it != resources.end()) {
			return it->second.first;
		}

		std::shared_ptr<T> resource = std::make_shared<T>();
		if (!resource->loadFromFile(filepath)) {
			return -1;
		}

		resources.insert(
			std::make_pair(filepath, std::make_pair(currentID, resource))
		);

		return currentID++;
	}

	void Remove(int id) {
		for (auto it = resources.begin(); it != resources.end(); it++) {
			if (it->second.first == id) {
				resources.erase(it->first);
			}
		}
	}

	std::shared_ptr<T> Get(int id) {
		for (auto it = resources.begin(); it != resources.end(); it++) {
			if (it->second.first == id) {
				return it->second.second;
			}
		}
		return nullptr;
	}

	bool Has(int id) {
		return Get(id) != nullptr;
	}

private:
	int currentID;
	std::map<std::string, std::pair<int, std::shared_ptr<T>>> resources;
};