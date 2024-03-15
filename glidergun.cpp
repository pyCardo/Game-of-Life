#include "main.hpp"

int main() {
  int const width{750};
  int const height{750};
  int const size{15};

  Board board{width, height, size};

  // squares
  board.data[setter(1, 5, width, size)].setAlive(true);
  board.data[setter(2, 5, width, size)].setAlive(true);
  board.data[setter(1, 6, width, size)].setAlive(true);
  board.data[setter(2, 6, width, size)].setAlive(true);
  board.data[setter(35, 3, width, size)].setAlive(true);  
  board.data[setter(36, 3, width, size)].setAlive(true);  
  board.data[setter(35, 4, width, size)].setAlive(true);
  board.data[setter(36, 4, width, size)].setAlive(true);

  // left
  board.data[setter(13, 3, width, size)].setAlive(true);
  board.data[setter(14, 3, width, size)].setAlive(true);
  board.data[setter(12, 4, width, size)].setAlive(true);
  board.data[setter(16, 4, width, size)].setAlive(true);
  board.data[setter(11, 5, width, size)].setAlive(true);
  board.data[setter(17, 5, width, size)].setAlive(true);
  board.data[setter(11, 6, width, size)].setAlive(true);
  board.data[setter(15, 6, width, size)].setAlive(true);
  board.data[setter(17, 6, width, size)].setAlive(true);
  board.data[setter(18, 6, width, size)].setAlive(true);
  board.data[setter(11, 7, width, size)].setAlive(true);
  board.data[setter(17, 7, width, size)].setAlive(true);
  board.data[setter(12, 8, width, size)].setAlive(true);
  board.data[setter(16, 8, width, size)].setAlive(true);
  board.data[setter(13, 9, width, size)].setAlive(true);
  board.data[setter(14, 9, width, size)].setAlive(true);

  // right
  board.data[setter(25, 1, width, size)].setAlive(true);
  board.data[setter(23, 2, width, size)].setAlive(true);
  board.data[setter(25, 2, width, size)].setAlive(true);
  board.data[setter(21, 3, width, size)].setAlive(true);
  board.data[setter(22, 3, width, size)].setAlive(true);
  board.data[setter(21, 4, width, size)].setAlive(true);
  board.data[setter(22, 4, width, size)].setAlive(true);
  board.data[setter(21, 5, width, size)].setAlive(true);
  board.data[setter(22, 5, width, size)].setAlive(true);
  board.data[setter(23, 6, width, size)].setAlive(true);
  board.data[setter(25, 6, width, size)].setAlive(true);
  board.data[setter(25, 7, width, size)].setAlive(true);

  board.play();
}