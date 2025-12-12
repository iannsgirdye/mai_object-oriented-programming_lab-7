#include "../../include/game/visitor.hpp"
#include <random>

Visitor::Visitor(const std::vector<std::unique_ptr<NPC>> &NPCs, const std::vector<Observer *> &observers): 
  NPCs_(NPCs), observers_(observers) {}

void Visitor::visit(NPC &attacker, NPC &defender) {
  if (!attacker.isAlive() || !defender.isAlive()) {
    return;
  }
  
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dice(1, 6);

  int attackerPower = dice(gen);
  int defenderPower = dice(gen);

  if (attacker.canKill(defender) && attackerPower > defenderPower) {
    defender.setAlive(false);
    notifyKill(attacker, defender);
  }
}

void Visitor::visit(NPC &npc, MoveDirection direction) {
  npc.move(direction);
  notifyMove(npc, direction);
}

void Visitor::notifyKill(NPC &killer, NPC &victim) const {
  for (size_t i = 0; i != observers_.size(); ++i) {
    if (observers_[i] == nullptr) {
      throw std::invalid_argument("Нет Observer");
    }
    observers_[i]->printKill(killer, victim);
  }
}

void Visitor::notifyMove(NPC &npc, MoveDirection direction) const {
  for (size_t i = 0; i != observers_.size(); ++i) {
    if (observers_[i] == nullptr) {
      throw std::invalid_argument("Нет Observer");
    }
    observers_[i]->printMove(npc, direction);
  }
}
