#include "../include/editor.hpp"
#include <fstream>
#include <string>

Editor::Editor() {
  observers_.push_back(new ScreenObserver());
  observers_.push_back(new FileObserver());
}

Editor::~Editor() {
  for (size_t i = 0; i != observers_.size(); ++i) {
    delete observers_[i];
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

void Editor::addNPC(const std::string &type, double x, double y, const std::string &name) {
  NPCs_.push_back(Factory::createNPC(type, x, y, name));
}

void Editor::saveToFile(const std::string &fileName) {
  std::ofstream out(fileName);

  if (!out.is_open()) {
    throw std::invalid_argument("Не удалось открыть файл для записи");
  }

  for (size_t i = 0; i != NPCs_.size(); ++i) {
    NPCs_[i]->save(out);
  }
}

void Editor::printNPCs() const {
  for (size_t i = 0; i != NPCs_.size(); ++i) {
    NPCs_[i]->save();
  }
}

void Editor::battle(const std::string &name, double range) {
  Visitor visitor(NPCs_, observers_, range);
  for (size_t i = 0; i != NPCs_.size(); ++i) {
    if (NPCs_[i]->getName() == name) {
      visitor.visit(*NPCs_[i]);
      return;
    }
  }

  throw std::invalid_argument("Персонажа с таким именем не существует");
}
