#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <vector>
#include <memory>
#include "./npc.hpp"
#include "./factory.hpp"
#include "./observer.hpp"
#include "./visitor.hpp"

class Observer;

class Editor {
  private:
    std::vector<std::unique_ptr<NPC>> NPCs_;
    std::vector<Observer *> observers_;

  public:
    Editor();
    ~Editor();
    
    void loadFromFile(const std::string &fileName);
    void saveToFile(const std::string &fileName);
    void addNPC(const std::string &type, double x, double y, const std::string &name);
    void printNPCs() const;
    void battle(const std::string &name, double range);
};

#endif
