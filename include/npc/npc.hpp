#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>

enum NPCType {
  UNKNOWN = 0,
  KNIGHT = 1,
  ELF = 2,
  DRAGON = 3
};

class NPC {
  protected:
    NPCType type_;
    double x_ = 0;
    double y_ = 0;
    std::string name_ = "";
    bool alive_ = true;
  public:
    NPC();
    NPC(NPCType type);
    NPC(NPCType type, double x, double y, const std::string &name);

    NPCType getType() const;
    std::string getTypeString() const;
    double getX() const;
    double getY() const;
    std::string getName() const;
    bool isAlive() const;

    void setAlive(bool alive);
    
    bool canKill(const NPC &other) const;
    double distance(const NPC &other) const;

    void load(std::ifstream &in);
    void save(std::ofstream &out) const;
    void save() const;

    friend std::iostream &operator>>(std::iostream &in, NPC &npc);
    friend std::ostream &operator<<(std::ostream &out, const NPC &npc);
};

NPCType convertTypeFromString(const std::string &type);

#endif
