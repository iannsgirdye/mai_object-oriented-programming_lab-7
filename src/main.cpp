#include "../include/game/editor.hpp"
#include "../include/values.hpp"
#include <iostream>
#include <string>

#define MODE_EXIT 2

void showMenu() {
  std::cout << "\n===> МЕНЮ <===\n";
  std::cout << "01. Показать меню\n";
  std::cout << "02. Выход\n";
  std::cout << "11. Добавить Странствующего рыцаря\n";
  std::cout << "12. Добавить Эльфа\n";
  std::cout << "13. Добавить Дракона\n";
  std::cout << "21. Показать конкретный NPC\n";
  std::cout << "22. Показать всех NPC\n";
  std::cout << "23. Сохранить в файл\n";
  std::cout << "24. Загрузить из файла\n";
  std::cout << "31. Запустить бой\n";
  std::cout << "32. Переместить NPC\n";
}

void modeAddNPC(Editor &editor, std::string type) {
  std::string name;
  double x;
  double y;
  char buffer[BUFSIZ];

  std::cout << "Имя ";
  std::cout << type;
  std::cout << ": ";
  std::cin >> name;

  std::sprintf(buffer, "Координата x [%f, %f]", MIN_X, MAX_X);
  std::cout << buffer;
  std::cin >> x;

  std::sprintf(buffer, "Координата y [%f, %f]", MIN_Y, MAX_Y);
  std::cout << buffer;
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
  int mode = 0;
  
  editor.initBaseNPCs();

  while (mode != MODE_EXIT) {
    try {
      std::cout << "\nВыберите действие (01 - меню): ";
      if (!(std::cin >> mode)) {
        std::cerr << "Конец входного потока или ошибка ввода!" << std::endl;
        break;
      }
              
      switch (mode) {
        case 1: showMenu(); break;
        case 2: modeExit(); break;
        case 11: modeAddNPC(editor, "Странствующего рыцаря"); break;
        case 12: modeAddNPC(editor, "Эльфа"); break;
        case 13: modeAddNPC(editor, "Дракона"); break;
        case 21: modePrintNPC(editor); break;
        case 22: modePrintAllNPC(editor); break;
        case 23: modeSaveToFile(editor); break;
        case 24: modeLoadFromFile(editor); break;
        case 31: modeBattle(editor); break;
        case 32: modeMove(editor); break;
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
