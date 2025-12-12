#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "../npc/npc.hpp"
#include "./observer.hpp"
#include <set>
#include <vector>
#include <memory>

enum FightResult {
  FIRST_WON,
  SECOND_WON,
  DRAW
};

class Observer;

class Visitor {
  private:
    const std::vector<std::unique_ptr<NPC>> &NPCs_;
    const std::vector<Observer *> &observers_;
    const double range_;

    FightResult fight(NPC &attacker, NPC &defender) const;  
    void notifyKill(NPC &killer, NPC &victin) const;
    void notifyMove(NPC &npc, MoveDirection direction) const;

  public:
    Visitor(const std::vector<std::unique_ptr<NPC>> &NPCs, const std::vector<Observer *> &observers, double range);
    void visit(NPC &attacker);
    void visit(NPC &npc, MoveDirection direction);
};

#endif
