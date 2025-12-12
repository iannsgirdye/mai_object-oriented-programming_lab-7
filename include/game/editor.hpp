#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <vector>
#include <memory>
#include <queue>
#include "../npc/npc.hpp"
#include "./factory.hpp"
#include "./observer.hpp"
#include "./visitor.hpp"

class Observer;

class Editor {
  private:
    std::vector<std::unique_ptr<NPC>> NPCs_;
    std::vector<Observer *> observers_;
    std::queue<std::pair<size_t, size_t>> battleQueue_;

  public:
    Editor();
    ~Editor();
    
    void initBaseNPCs();
    void loadFromFile(const std::string &fileName);
    void saveToFile(const std::string &fileName) const;
    void addNPC(NPCType type, double x, double y, const std::string &name);
    void addNPC(const std::string &type, double x, double y, const std::string &name);
    void printNPC(const std::string &name) const;
    void printAreAliveNPCs() const;
    void printNPCs() const;
    void detectBattles();
    void processBattles();
    void move(const std::string &name, MoveDirection direction) const;
    void moveNPCs(std::mt19937 &random);
};

#endif
