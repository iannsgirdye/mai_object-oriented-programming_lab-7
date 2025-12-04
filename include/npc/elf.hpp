#ifndef ELF_HPP
#define ELF_HPP

#include "./npc.hpp"

class Elf: public NPC {
  public:
    Elf();
    Elf(double x, double y, const std::string &name);
};

#endif
