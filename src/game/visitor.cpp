#include "../../include/game/visitor.hpp"
#include <random>

Visitor::Visitor(std::vector<std::unique_ptr<NPC>> &NPCs, std::vector<Observer *> &observers, double range): 
  NPCs_(NPCs), observers_(observers), range_(range) {}

FightResult Visitor::fight(NPC &first, NPC &second) const {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dice(1, 6);

  int firstPower = dice(gen);
  int secondPower = dice(gen);

  if (first.canKill(second) && firstPower > secondPower) {
    return FightResult::FIRST_WON;
  }
  if (second.canKill(first) && secondPower > firstPower) {
    return FightResult::SECOND_WON;
  }
  return FightResult::DRAW;
}

void Visitor::visit(NPC &attacker) {
  if (!attacker.isAlive()) {
    return;
  }

  size_t attackerIndex = NPCs_.size();
  for (size_t i = 0; i != NPCs_.size(); ++i) {
    if (attacker.getName() == NPCs_[i]->getName()) {
      attackerIndex = i;
      break;
    }
  }
  if (attackerIndex == NPCs_.size()) {
    throw std::invalid_argument("Персонажа с таким именем не существует");
  }

  for (size_t i = 0; i != NPCs_.size(); ++i) {
    if (i == attackerIndex) {
      continue;
    }
    if (NPCs_[i] == nullptr) {
      continue;
    }
    
    NPC &defender = *NPCs_[i];
    if (!defender.isAlive()) {
      continue;
    }
    if (attacker.distance(defender) > range_) {
      continue;
    }
    
    switch (fight(attacker, defender)) {
      case FightResult::FIRST_WON:
        notifyKill(attacker, defender);
        defender.setAlive(false);
        break;
      case FightResult::SECOND_WON:
        notifyKill(defender, attacker);
        attacker.setAlive(false);
        return;
      case FightResult::DRAW:
        break;
    }
  }
}

void Visitor::notifyKill(NPC &killer, NPC &victim) const {
  for (size_t i = 0; i != observers_.size(); ++i) {
    if (observers_[i] == nullptr) {
      throw std::invalid_argument("Нет Observer");
    }
    observers_[i]->printKill(killer, victim);
  }
}