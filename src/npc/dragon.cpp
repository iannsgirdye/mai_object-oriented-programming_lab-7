#include "../../include/npc/npc.hpp"
#include "../../include/npc/dragon.hpp"

Dragon::Dragon(): NPC(NPCType::DRAGON) {}

Dragon::Dragon(double x, double y, const std::string &name): NPC(NPCType::DRAGON, x, y, name) {}
