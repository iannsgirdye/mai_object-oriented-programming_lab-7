#include "../include/game/editor.hpp"
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <random>

std::atomic<bool> gameOver{false};
std::mutex coutMutex;
std::shared_mutex editorMutex;

void threadMoveNPCsAndDetectBattles(Editor &editor) {
  std::mt19937 random(std::random_device{}());
  while (!gameOver) {
    {
      std::unique_lock lock(editorMutex);
      editor.moveNPCs(random);
      editor.detectBattles();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
}

void threadProcessBattles(Editor &editor) {
  while (!gameOver) {
    {
      std::unique_lock lock(editorMutex);
      editor.processBattles();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void threadPrintNPCs(Editor &editor) {
  while (!gameOver) {
    {
      std::shared_lock lock(editorMutex);
      std::lock_guard<std::mutex> cout_lock(coutMutex);
      editor.printNPCs();
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

int main() {
  int64_t secondsOfGame;
  std::cout << "Введите длительность игры в секундах: ";
  std::cin >> secondsOfGame;

  Editor editor;
  editor.initBaseNPCs();

  std::thread t_move(threadMoveNPCsAndDetectBattles, std::ref(editor));
  std::thread t_battle(threadProcessBattles, std::ref(editor));
  std::thread t_print(threadPrintNPCs, std::ref(editor));

  std::this_thread::sleep_for(std::chrono::seconds(secondsOfGame));
  gameOver = true;

  t_move.join();
  t_battle.join();
  t_print.join();

  {
    std::shared_lock lock(editorMutex);
    std::lock_guard<std::mutex> cout_lock(coutMutex);
    std::cout << "\nИгра окончена! Выжившие NPC:\n";
    editor.printAreAliveNPCs();
  }
  return 0;
}
