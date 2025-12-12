#include "../../include/npc/npc.hpp"
#include "../../include/npc/dragon.hpp"
#include "../../include/values.hpp"

Dragon::Dragon(): NPC(NPCType::DRAGON) {}

Dragon::Dragon(double x, double y, const std::string &name): 
  NPC(NPCType::DRAGON, x, y, name, DRAGON_MOVE_DISTANCE, DRAGON_ATTACK_RANGE) {}
