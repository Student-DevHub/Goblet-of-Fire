#include "ResourceManager.hpp"

namespace GobletOfFire {
  namespace Core {
    std::string ResourcePath::resources_directory_("resources/");
    std::map<uint64_t, std::string> ResourcePath::paths_ = {
      {100, "background1.png"},
      {101, "main_scene_base.png"},
      {102, "main_scene_o1.png"},
      {103, "main_scene_o2.png"},
      {104, "main_scene_o3.png"}
        //add more mappings
    };
  }
}