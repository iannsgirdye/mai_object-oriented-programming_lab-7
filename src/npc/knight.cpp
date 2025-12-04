#include "../../include/npc/npc.hpp"
#include "../../include/npc/knight.hpp"

Knight::Knight(): NPC(NPCType::KNIGHT) {}

Knight::Knight(double x, double y, const std::string &name): NPC(NPCType::KNIGHT, x, y, name) {}
