#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "./npc.hpp"
#include <memory>
#include <string>
#include <fstream>

class Factory {
  public:
    static std::unique_ptr<NPC> createNPC(const std::string &type);
    static std::unique_ptr<NPC> createNPC(const std::string &type, double x, double y, const std::string &name);
    static std::unique_ptr<NPC> loadNPCFromFile(std::ifstream &file);
};

#endif
