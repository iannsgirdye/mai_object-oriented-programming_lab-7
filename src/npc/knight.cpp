#include "../../include/npc/npc.hpp"
#include "../../include/npc/knight.hpp"
#include "../../include/values.hpp"

Knight::Knight(): NPC(NPCType::KNIGHT) {}

Knight::Knight(double x, double y, const std::string &name):
  NPC(NPCType::KNIGHT, x, y, name, KNIGHT_MOVE_DISTANCE, KNIGHT_ATTACK_RANGE) {}
