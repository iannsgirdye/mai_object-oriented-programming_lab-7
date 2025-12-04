#include "../include/observer.hpp"
#include <iostream>

void ScreenObserver::printKill(const NPC &killer, const NPC &victim) {
  std::cout << killer.getName() << " убил " << victim.getName() << std::endl;
}

FileObserver::FileObserver() {
  file_.open("./log.txt");
}

void FileObserver::printKill(const NPC &killer, const NPC &victim) {
  if (file_.is_open()) {
    file_ << killer.getName() << " убил " << victim.getName() << std::endl;
  }
}

FileObserver::~FileObserver() {
  if (file_.is_open()) {
    file_.close();
  }
}
