#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "./npc.hpp"

class Knight: public NPC {
  public:
    Knight();
    Knight(double x, double y, const std::string &name);
};

#endif
