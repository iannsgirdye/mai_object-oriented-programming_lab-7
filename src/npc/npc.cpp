#include "../../include/npc/npc.hpp"
#include <string>
#include <cmath>
#include <array>
#include <algorithm>

#define MIN_X 0.0
#define MAX_X 1000.0
#define MIN_Y 0.0
#define MAX_Y 1000.0

NPC::NPC(): type_(NPCType::UNKNOWN) {}

NPC::NPC(NPCType type): type_(type) {}

NPC::NPC(NPCType type, double x, double y, const std::string &name): type_(type), x_(x), y_(y), name_(name) {}

NPCType NPC::getType() const {
  return type_;
}

std::string NPC::getTypeString() const {
  switch (type_) {
    case NPCType::KNIGHT: return "Странствующий рыцарь";
    case NPCType::ELF: return "Эльф";
    case NPCType::DRAGON: return "Дракон";
  }
  return "Неизвестный";
}

double NPC::getX() const {
  return x_;
}

double NPC::getY() const {
  return y_;
}

std::string NPC::getName() const {
  return name_;
}

bool NPC::isAlive() const {
  return alive_;
}

void NPC::setAlive(bool alive) {
  alive_ = alive;
}

void NPC::move(MoveDirection direction) {
  if (!isAlive()) {
    return;
  }

  std::array<double, 4> moveDistances = {0.0, 30.0, 10.0, 50.0};
  double thisMoveDistance = moveDistances[static_cast<int>(getType())];
  switch (direction) {
    case MoveDirection::TOP: y_ = std::clamp(MIN_Y, y_ + thisMoveDistance, MAX_Y); break;
    case MoveDirection::RIGHT: x_ = std::clamp(MIN_X, x_ + thisMoveDistance, MAX_X); break;
    case MoveDirection::BOTTOM: y_ = std::clamp(MIN_Y, y_ - thisMoveDistance, MAX_Y); break;
    case MoveDirection::LEFT: x_ = std::clamp(MIN_X, x_ - thisMoveDistance, MAX_X); break;
  }
}

bool NPC::canKill(const NPC &other) const {
  switch (type_) {
    case NPCType::KNIGHT: return (other.type_ == NPCType::DRAGON) ? true : false;
    case NPCType::ELF: return (other.type_ == NPCType::KNIGHT) ? true : false;
    case NPCType::DRAGON: return true;
  }
  return false;
}

void NPC::load(std::ifstream &in) {
  std::string type;
  in >> type >> name_ >> x_ >> y_;
  type_ = convertTypeFromString(type);
}

void NPC::save(std::ofstream &out) const {
  out << getTypeString() << " "
      << name_ << " "
      << x_ << " "
      << y_ << std::endl;
}

void NPC::save() const {
  std::cout << getTypeString() << " " 
            << name_ << " "
            << x_ << " "
            << y_ << std::endl;
}

double NPC::distance(const NPC &other) const {
  const double distanceX = x_ - other.x_;
  const double distanceY = y_ - other.y_;
  return std::sqrt(distanceX * distanceX + distanceY * distanceY);
}

std::iostream &operator>>(std::iostream &in, NPC &npc) {
  std::string type;
  in >> type >> npc.x_ >> npc.y_ >> npc.name_;
  npc.type_ = convertTypeFromString(type);
  return in;
}

std::ostream &operator<<(std::ostream &out, const NPC &npc) {
  out << "NPC: "
      << "type=\"" << npc.getTypeString() << "\", "
      << "name=" << npc.name_ << ", "
      << "x=" << npc.x_ << ", "
      << "y=" << npc.y_ << ", "
      << "alive=" << npc.alive_ << std::endl;
  return out;
}

NPCType convertTypeFromString(const std::string &type) {
  if (type == "Странствующий рыцарь") return NPCType::KNIGHT;
  if (type == "Эльф") return NPCType::ELF;
  if (type == "Дракон") return NPCType::DRAGON;
  return NPCType::UNKNOWN;
}
