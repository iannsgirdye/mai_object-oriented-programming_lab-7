#include "../../include/npc/npc.hpp"
#include "../../include/npc/elf.hpp"
#include "../../include/values.hpp"

Elf::Elf(): NPC(NPCType::ELF) {}

Elf::Elf(double x, double y, const std::string &name): 
  NPC(NPCType::ELF, x, y, name, ELF_MOVE_DISTANCE, ELF_ATTACK_RANGE) {}
