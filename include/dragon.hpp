#ifndef DRAGON_HPP
#define DRAGON_HPP

#include "./npc.hpp"

class Dragon: public NPC {
  public:
    Dragon();
    Dragon(double x, double y, const std::string &name);
};

#endif
