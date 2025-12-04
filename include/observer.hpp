#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <fstream>
#include "./npc.hpp"
#include "./editor.hpp"

class Observer {
  public:
    virtual ~Observer() = default;
    virtual void printKill(const NPC &killer, const NPC &victim) = 0;
};

class ScreenObserver: public Observer {
  public:
    void printKill(const NPC &killer, const NPC &victim) override;
};

class FileObserver: public Observer{
  private:
    std::ofstream file_;

  public:
    FileObserver();

    void printKill(const NPC &killer, const NPC &victim) override;

    ~FileObserver();
};

#endif
