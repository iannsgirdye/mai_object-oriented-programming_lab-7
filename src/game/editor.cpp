#include "../../include/game/editor.hpp"
#include "../../include/values.hpp"
#include <fstream>
#include <string>
#include <random>

Editor::Editor() {
  observers_.push_back(new ScreenObserver());
  observers_.push_back(new FileObserver());
}

Editor::~Editor() {
  for (size_t i = 0; i != observers_.size(); ++i) {
    delete observers_[i];
  }
}

void Editor::initBaseNPCs() {
  NPCs_.reserve(COUNT_BASE_NPCS);

  NPCType type;
  double x;
  double y;
  std::string name;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> x_dist(MIN_X, MAX_X);
  std::uniform_real_distribution<double> y_dist(MIN_Y, MAX_Y);

  for (size_t i = 0; i != COUNT_BASE_NPCS; ++i) {
    type = static_cast<NPCType>(1 + (i % 3));
    x = x_dist(gen);
    y = y_dist(gen);
    name = "BaseNPC_" + std::to_string(i + 1);
    addNPC(type, x, y, name);
  }
}

void Editor::loadFromFile(const std::string &fileName) {
  std::ifstream in(fileName);

  if (!in.is_open()) {
    throw std::invalid_argument("Не удалось открыть файл для чтения");
  }

  std::unique_ptr<NPC> npc;
  while ((npc = Factory::loadNPCFromFile(in)) != nullptr) {
    NPCs_.push_back(std::move(npc));
  }
  
  in.close();
}

void Editor::saveToFile(const std::string &fileName) const {
  std::ofstream out(fileName);

  if (!out.is_open()) {
    throw std::invalid_argument("Не удалось открыть файл для записи");
  }

  for (size_t i = 0; i != NPCs_.size(); ++i) {
    NPCs_[i]->save(out);
  }
}

void Editor::printNPC(const std::string &name) const {
  for (size_t i = 0; i != NPCs_.size(); ++i) {
    if (NPCs_[i]->getName() == name) {
      NPCs_[i]->save();
      return;
    }
  }
}

void Editor::printNPCs() const {
  for (size_t i = 0; i != NPCs_.size(); ++i) {
    NPCs_[i]->save();
  }
}

void Editor::printAreAliveNPCs() const {
  for (size_t i = 0; i != NPCs_.size(); ++i) {
    if (NPCs_[i]->isAlive()) {
      NPCs_[i]->save();
    }
  }
}

void Editor::addNPC(NPCType type, double x, double y, const std::string &name) {
  NPCs_.push_back(Factory::createNPC(type, x, y, name));
}

void Editor::addNPC(const std::string &type, double x, double y, const std::string &name) {
  addNPC(convertTypeFromString(type), x, y, name);
}

void Editor::detectBattles() {
  for (size_t i = 0; i != NPCs_.size(); ++i) {
    for (size_t j = i + 1; j != NPCs_.size(); ++j) {
      if (NPCs_[i]->canKill(*NPCs_[j])) {
        battleQueue_.push({i, j});
      } else if (NPCs_[j]->canKill(*NPCs_[i])) {
        battleQueue_.push({j, i});
      }
    }
  }
}

void Editor::processBattles() {
  Visitor visitor(NPCs_, observers_);
  while (!battleQueue_.empty()) {
    auto [attackerIndex, defenderIndex] = battleQueue_.front();
    battleQueue_.pop();
    visitor.visit(*NPCs_[attackerIndex], *NPCs_[defenderIndex]);
  }
}

void Editor::move(const std::string &name, MoveDirection direction) const {
  Visitor visitor(NPCs_, observers_);
  for (size_t i = 0; i != NPCs_.size(); ++i) {
    if (NPCs_[i]->getName() == name) {
      visitor.visit(*NPCs_[i], direction);
      return;
    }
  }
}

void Editor::moveNPCs(std::mt19937 &random) {
  std::uniform_int_distribution<int> directionDistribution(0, 3);

  Visitor visitor(NPCs_, observers_);
  for (size_t i = 0; i != NPCs_.size(); ++i) {
    MoveDirection direction = static_cast<MoveDirection>(directionDistribution(random));
    visitor.visit(*NPCs_[i], direction);
  }
}
