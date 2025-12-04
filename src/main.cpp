#include "../include/editor.hpp"
#include <iostream>
#include <string>

void showMenu() {
  std::cout << "\n===> МЕНЮ <===\n";
  std::cout << "1. Добавить Странствующего рыцаря\n";
  std::cout << "2. Добавить Эльфа\n";
  std::cout << "3. Добавить Дракона\n";
  std::cout << "4. Показать всех NPC\n";
  std::cout << "5. Сохранить в файл\n";
  std::cout << "6. Загрузить из файла\n";
  std::cout << "7. Боевой режим\n";
  std::cout << "8. Показать меню\n";
  std::cout << "9. Выход\n";
}

void mode1(Editor &editor) {
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

void mode2(Editor &editor) {
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

void mode3(Editor &editor) {
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

void mode4(Editor &editor) {
  editor.printNPCs();
}

void mode5(Editor &editor) {
  std::string filename;
  std::cout << "Имя файла для сохранения: ";
  std::cin >> filename;
  editor.saveToFile(filename);
}

void mode6(Editor &editor) {
  std::string filename;
  std::cout << "Имя файла для загрузки: ";
  std::cin >> filename;
  editor.loadFromFile(filename);
}

void mode7(Editor &editor) {
  std::string name;
  double range;
  std::cout << "Имя персонажа: ";
  std::cin >> name;
  std::cout << "Радиус боя: ";
  std::cin >> range;
  editor.battle(name, range);
}

void modeExit() {
  std::cout << "Игра окончена!\n";
}

void modeError() {
  std::cout << "Несуществующее действие\n";
}

int main() {
  Editor editor;
  int mode;
  
  showMenu();

  while (true) {
    try {
      std::cout << "\nВыберите действие: ";
      if (!(std::cin >> mode)) {
        std::cerr << "Конец входного потока или ошибка ввода!" << std::endl;
        break;
      }
              
      switch (mode) {
        case 1: mode1(editor); break;
        case 2: mode2(editor); break;
        case 3: mode3(editor); break;
        case 4: mode4(editor); break;
        case 5: mode5(editor); break;
        case 6: mode6(editor); break;
        case 7: mode7(editor); break;
        case 8: showMenu(); break;
        case 9: modeExit(); return 0;
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
