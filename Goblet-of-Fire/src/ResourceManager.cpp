#include "ResourceManager.hpp"

namespace GobletOfFire {
  namespace Core {
    std::string ResourcePath::resources_directory_("resources/");
    std::map<uint64_t, std::string> ResourcePath::paths_ = {
        {1, "img1.png"},
        //add more mappings
    };
  }
}