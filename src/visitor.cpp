#include "../include/visitor.hpp"

Visitor::Visitor(std::vector<std::unique_ptr<NPC>> &NPCs, std::vector<Observer *> &observers, double range): 
  NPCs_(NPCs), observers_(observers), range_(range) {}

FightResult Visitor::fight(NPC &first, NPC &second) const {
  if (first.canKill(second) && second.canKill(first)) {
    return FightResult::BOTH_KILLED;
  }
  if (first.canKill(second)) {
    return FightResult::SECOND_KILLED;
  }
  if (second.canKill(first)) {
    return FightResult::FIRST_KILLED;
  }
  return FightResult::NO_KILLED;
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
      case BOTH_KILLED:
        notifyKill(attacker, defender);
        notifyKill(defender, attacker);
        attacker.setAlive(false);
        defender.setAlive(false);
        return;
      case FightResult::SECOND_KILLED:
        notifyKill(attacker, defender);
        defender.setAlive(false);
        break;
      case FightResult::FIRST_KILLED:
        notifyKill(defender, attacker);
        attacker.setAlive(false);
        return;
      case FightResult::NO_KILLED:
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