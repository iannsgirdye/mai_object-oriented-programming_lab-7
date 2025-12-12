#include "../include/game/editor.hpp"
#include <iostream>
#include <string>

void showMenu() {
  std::cout << "\n===> МЕНЮ <===\n";
  std::cout << " 1. Добавить Странствующего рыцаря\n";
  std::cout << " 2. Добавить Эльфа\n";
  std::cout << " 3. Добавить Дракона\n";
  std::cout << " 4. Показать конкретный NPC\n";
  std::cout << " 5. Показать всех NPC\n";
  std::cout << " 6. Сохранить в файл\n";
  std::cout << " 7. Загрузить из файла\n";
  std::cout << " 8. Запустить бой\n";
  std::cout << " 9. Переместить персонажа\n";
  std::cout << "10. Показать меню\n";
  std::cout << " 0. Выход\n";
}

void modeAddKnight(Editor &editor) {
  std::string type = "Странствующий рыцарь";
  std::string name;
  double x;
  double y;

  std::cout << "Имя Странствующего рыцаря: ";
  std::cin >> name;
  std::cout << "Координата x [0; 500]: ";
  std::cin >> x;
  std::cout << "Координата y [0; 500]: ";
  std::cin >> y;
  
  editor.addNPC(type, x, y, name);
}

void modeAddElf(Editor &editor) {
  std::string type = "Эльф";
  std::string name;
  double x;
  double y;

  std::cout << "Имя Эльфа: ";
  std::cin >> name;
  std::cout << "Координата x [0; 500]: ";
  std::cin >> x;
  std::cout << "Координата y [0; 500]: ";
  std::cin >> y;
  
  editor.addNPC(type, x, y, name);
}

void modeAddDragon(Editor &editor) {
  std::string type = "Дракон";
  std::string name;
  double x;
  double y;

  std::cout << "Имя Дракона: ";
  std::cin >> name;
  std::cout << "Координата x [0; 500]: ";
  std::cin >> x;
  std::cout << "Координата y [0; 500]: ";
  std::cin >> y;
  
  editor.addNPC(type, x, y, name);
}

void modePrintNPC(Editor &editor) {
  std::string name;
  std::cout << "Имя персонажа: ";
  std::cin >> name;
  editor.printNPC(name);
}

void modePrintAllNPC(Editor &editor) {
  editor.printNPCs();
}

void modeSaveToFile(Editor &editor) {
  std::string filename;
  std::cout << "Имя файла для сохранения: ";
  std::cin >> filename;
  editor.saveToFile(filename);
}

void modeLoadFromFile(Editor &editor) {
  std::string filename;
  std::cout << "Имя файла для загрузки: ";
  std::cin >> filename;
  editor.loadFromFile(filename);
}

void modeBattle(Editor &editor) {
  std::string name;
  double range;
  std::cout << "Имя персонажа: ";
  std::cin >> name;
  std::cout << "Радиус боя: ";
  std::cin >> range;
  editor.battle(name, range);
}

void modeMove(Editor &editor) {
  std::string name;
  std::string direction;
  std::cout << "Имя персонажа: ";
  std::cin >> name;
  std::cout << "Направление перемещения (вверх/вправо/вниз/влево): ";
  std::cin >> direction;
  editor.move(name, convertDirectionFromString(direction));
}

void modeExit() {
  std::cout << "Игра окончена!\n";
}

void modeError() {
  std::cout << "Несуществующее действие\n";
}

int main() {
  Editor editor;
  int mode = -1;
  
  editor.initBaseNPCs();
  
  showMenu();

  while (mode != 0) {
    try {
      std::cout << "\nВыберите действие: ";
      if (!(std::cin >> mode)) {
        std::cerr << "Конец входного потока или ошибка ввода!" << std::endl;
        break;
      }
              
      switch (mode) {
        case 1: modeAddKnight(editor); break;
        case 2: modeAddElf(editor); break;
        case 3: modeAddDragon(editor); break;
        case 4: modePrintNPC(editor); break;
        case 5: modePrintAllNPC(editor); break;
        case 6: modeSaveToFile(editor); break;
        case 7: modeLoadFromFile(editor); break;
        case 8: modeBattle(editor); break;
        case 9: modeMove(editor); break;
        case 10: showMenu(); break;
        case 0: modeExit(); break;
        default: modeError(); break;
      }
    } catch (const std::exception& e) {
      std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (...) {
      std::cerr << "Неизвестная ошибка!" << std::endl;
    }
  }
    
  return 0;
}
