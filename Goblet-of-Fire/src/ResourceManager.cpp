#include "ResourceManager.hpp"

namespace GobletOfFire {
  namespace Core {
    std::string ResourcePath::resources_directory_("resources/");
    std::map<uint64_t, std::string> ResourcePath::paths_ = {
      {99, "background2.png"},
      {100, "background1.png"},
      {101, "main_scene_base.png"},
      {102, "main_scene_o1.png"},
      {103, "main_scene_o2.png"},
      {104, "main_scene_o3.png"},
      {110, "character_selection_a_base.png"},
      {111, "character_selection_a_o1.png"},
      {112, "character_selection_a_o2.png"},
      {113, "character_selection_a_o3.png"},
      {114, "character_selection_a_o4.png"},
      {115, "character_selection_a_o5.png"},
      {116, "character_selection_a_o6.png"},
      {120, "character_selection_b_base.png"},
      {121, "character_selection_b_o1.png"},
      {122, "character_selection_b_o2.png"},
      {123, "character_selection_b_o3.png"},
      {124, "character_selection_b_o4.png"},
      {125, "character_selection_b_o5.png"},
      {126, "character_selection_b_o6.png"},
      {1, "igris_sprite_sheet.png"},
      {50, "map_1_bg.png"},
      {51, "map_1_fg.png"}, 
      {52, "map_1_ledge.png"},
      {150, "health_bar_1_1.png"},
      {151, "health_bar_1_2.png"},
      {152, "health_bar_1_3.png"},
      {153, "health_bar_2_1.png"},
      {154, "health_bar_2_2.png"},
      {155, "health_bar_2_3.png"},
      {200, "winner_a.png"},
      {201, "winner_b.png"}
        //add more mappings
    };
  }
}