// life.cpp

#include <iostream>
#include <chrono>
#include <thread>

#include "grid.h"
#include "life.h"

using namespace std::chrono_literals;

int main() {
  std::cout << "Game of Life, press enter to start" << std::endl;

  std::cin.get();

  // Clear the screen once
  std::cout << "\x1b[2J";

  Grid current;

  current.randomise();

  while(true) {
    current.draw();

    std::this_thread::sleep_for(300ms);

    Grid next;

    calculate(current, next);
    current.update(next);
  }
}
