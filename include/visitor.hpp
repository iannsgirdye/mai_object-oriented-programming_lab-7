#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "./npc.hpp"
#include "./observer.hpp"
#include <set>
#include <vector>
#include <memory>

enum FightResult {
  NO_KILLED = 0,
  FIRST_KILLED = 1,
  SECOND_KILLED = 2,
  BOTH_KILLED = 3
};

class Observer;

class Visitor {
  private:
    std::vector<std::unique_ptr<NPC>> &NPCs_;
    std::vector<Observer *> &observers_;
    double range_;

    FightResult fight(NPC &attacker, NPC &defender) const;  
    void notifyKill(NPC &killer, NPC &victin) const;

  public:
    Visitor(std::vector<std::unique_ptr<NPC>> &NPCs, std::vector<Observer *> &observers, double range);
    void visit(NPC &attacker);
};

#endif
