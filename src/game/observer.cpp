#include "../../include/game/observer.hpp"
#include <iostream>

void ScreenObserver::printKill(const NPC &killer, const NPC &victim) {
  std::cout << killer.getName() << " убил " << victim.getName() << std::endl;
}

void ScreenObserver::printMove(const NPC &npc, MoveDirection direction) {
  std::cout << npc.getName() << " переместился " << convertDirectionToString(direction) << std::endl;
}

FileObserver::FileObserver() {
  file_.open("./log.txt");
}

void FileObserver::printKill(const NPC &killer, const NPC &victim) {
  if (file_.is_open()) {
    file_ << killer.getName() << " убил " << victim.getName() << std::endl;
  }
}

void FileObserver::printMove(const NPC &npc, MoveDirection direction) {
  if (file_.is_open()) {
    std::cout << npc.getName() << " переместился " << convertDirectionToString(direction) << std::endl;
  }
}

FileObserver::~FileObserver() {
  if (file_.is_open()) {
    file_.close();
  }
}
