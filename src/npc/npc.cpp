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

NPC::NPC(NPCType type, double x, double y, const std::string &name, int moveDistance, int attackRange): 
  type_(type), x_(x), y_(y), name_(name), moveDistance_(moveDistance), attackRange_(attackRange) {}

NPCType NPC::getType() const {
  return type_;
}

std::string NPC::getTypeString() const {
  switch (type_) {
    case NPCType::KNIGHT: return "Странствующий рыцарь";
    case NPCType::ELF: return "Эльф";
    case NPCType::DRAGON: return "Дракон";
    default: return "Неизвестный";
  }
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

int NPC::getMoveDistance() const {
  return moveDistance_;
}

int NPC::getAttackRange() const {
  return attackRange_;
}

void NPC::move(MoveDirection direction) {
  if (!isAlive()) {
    return;
  }

  switch (direction) {
    case MoveDirection::TOP: y_ = std::clamp(MIN_Y, y_ + moveDistance_, MAX_Y); break;
    case MoveDirection::RIGHT: x_ = std::clamp(MIN_X, x_ + moveDistance_, MAX_X); break;
    case MoveDirection::BOTTOM: y_ = std::clamp(MIN_Y, y_ - moveDistance_, MAX_Y); break;
    case MoveDirection::LEFT: x_ = std::clamp(MIN_X, x_ - moveDistance_, MAX_X); break;
  }
}

bool NPC::canKill(const NPC &other) const {
  if (!isAlive() || !other.isAlive()) {
    return false;
  }

  switch (type_) {
    case NPCType::KNIGHT: return (other.type_ == NPCType::DRAGON) ? true : false;
    case NPCType::ELF: return (other.type_ == NPCType::KNIGHT) ? true : false;
    case NPCType::DRAGON: return true;
    default: return false;
  }
  return false;
}

void NPC::load(std::ifstream &in) {
  std::string type;
  in >> type >> name_ >> x_ >> y_;
  type_ = convertTypeFromString(type);
}

void NPC::save(std::ofstream &out) const {
  if (!isAlive()) {
    return;
  }

  out << getTypeString() << " "
      << name_ << " "
      << x_ << " "
      << y_ << " "
      << isAlive() << "\n";
}

void NPC::save() const {
  std::cout << getTypeString() << " " 
            << name_ << " "
            << x_ << " "
            << y_ << " "
            << isAlive() << "\n";
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

MoveDirection convertDirectionFromString(const std::string &direction) {
  if (direction == "вверх") return MoveDirection::TOP;
  if (direction == "вправо") return MoveDirection::RIGHT;
  if (direction == "вниз") return MoveDirection::BOTTOM;
  if (direction == "влево") return MoveDirection::LEFT;
  throw std::invalid_argument("Некорректное направление движения");
}

std::string convertDirectionToString(MoveDirection direction) {
  switch (direction) {
    case MoveDirection::TOP: return "вверх";
    case MoveDirection::RIGHT: return "вправо";
    case MoveDirection::BOTTOM: return "вниз";
    case MoveDirection::LEFT: return "влево";
    default: throw std::invalid_argument("Некорректное направление движения");
  }
}
