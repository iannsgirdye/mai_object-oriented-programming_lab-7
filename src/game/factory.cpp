#include "../../include/game/factory.hpp"
#include "../../include/npc/knight.hpp"
#include "../../include/npc/elf.hpp"
#include "../../include/npc/dragon.hpp"
#include <stdexcept>

#define MIN_X 0
#define MAX_X 500
#define MIN_Y 0
#define MAX_Y 500

std::unique_ptr<NPC> Factory::createNPC(NPCType type) {
  return createNPC(type, MIN_X, MIN_Y, "");
}

std::unique_ptr<NPC> Factory::createNPC(NPCType type, double x, double y, const std::string &name) {
  if (x < MIN_X || x > MAX_X || y < MIN_Y || y > MAX_Y) {
    char buffer[BUFSIZ];
    std::sprintf(buffer, "Каждая координата должна быть в диапазоне [%d, %d]", MIN_X, MAX_X);
    throw std::invalid_argument(buffer);
  }

  switch (type) {
    case NPCType::KNIGHT: return std::make_unique<Knight>(x, y, name);
    case NPCType::ELF: return std::make_unique<Elf>(x, y, name);
    case NPCType::DRAGON: return std::make_unique<Dragon>(x, y, name);
    default: throw std::invalid_argument("Неизвестный тип NPC");
  }
}

std::unique_ptr<NPC> Factory::loadNPCFromFile(std::ifstream &file) {
  std::string type;
  std::string name;
  double x;
  double y;
  
  if (file >> type >> x >> y >> name) {
    return createNPC(convertTypeFromString(type), x, y, name);
  }
  return nullptr;
}
