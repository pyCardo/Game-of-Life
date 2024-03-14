#include "main.hpp"

int main() {
  int const width{400};
  int const height{400};
  int const size{8};

  Grid grid{width, height, size};

  // first glider
  grid.data[setter(11, 3, width, size)].setAlive(true);
  grid.data[setter(12, 4, width, size)].setAlive(true);
  grid.data[setter(10, 5, width, size)].setAlive(true);
  grid.data[setter(11, 5, width, size)].setAlive(true);
  grid.data[setter(12, 5, width, size)].setAlive(true);

  // second glider
  grid.data[setter(25, 18, width, size)].setAlive(true);
  grid.data[setter(26, 18, width, size)].setAlive(true);
  grid.data[setter(25, 19, width, size)].setAlive(true);
  grid.data[setter(27, 19, width, size)].setAlive(true);
  grid.data[setter(25, 20, width, size)].setAlive(true);

  // beacon
  grid.data[setter(14, 13, width, size)].setAlive(true);
  grid.data[setter(15, 13, width, size)].setAlive(true);
  grid.data[setter(14, 14, width, size)].setAlive(true);
  grid.data[setter(17, 16, width, size)].setAlive(true);
  grid.data[setter(16, 16, width, size)].setAlive(true);
  grid.data[setter(17, 15, width, size)].setAlive(true);

  grid.play();
}