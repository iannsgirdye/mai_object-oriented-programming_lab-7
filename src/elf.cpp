#include "../include/npc.hpp"
#include "../include/elf.hpp"

Elf::Elf(): NPC(NPCType::ELF) {}

Elf::Elf(double x, double y, const std::string &name): NPC(NPCType::ELF, x, y, name) {}
