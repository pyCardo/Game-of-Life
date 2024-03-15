#include "main.hpp"

int main() {
  int const width{750};
  int const height{750};
  int const size{15};

  Board board{width, height, size};

  // first glider
  board.data[setter(11, 3, width, size)].setAlive(true);
  board.data[setter(12, 4, width, size)].setAlive(true);
  board.data[setter(10, 5, width, size)].setAlive(true);
  board.data[setter(11, 5, width, size)].setAlive(true);
  board.data[setter(12, 5, width, size)].setAlive(true);

  // second glider
  board.data[setter(25, 18, width, size)].setAlive(true);
  board.data[setter(26, 18, width, size)].setAlive(true);
  board.data[setter(25, 19, width, size)].setAlive(true);
  board.data[setter(27, 19, width, size)].setAlive(true);
  board.data[setter(25, 20, width, size)].setAlive(true);

  // beacon
  board.data[setter(14, 13, width, size)].setAlive(true);
  board.data[setter(15, 13, width, size)].setAlive(true);
  board.data[setter(14, 14, width, size)].setAlive(true);
  board.data[setter(17, 16, width, size)].setAlive(true);
  board.data[setter(16, 16, width, size)].setAlive(true);
  board.data[setter(17, 15, width, size)].setAlive(true);

  board.play();
}