#include "main.hpp"

int main() {
  int const width{600};
  int const height{400};
  int const size{10};

  Grid grid{width, height, size};

  grid.data[setter(13, 11, width, size)].setAlive(true);
  grid.data[setter(14, 11, width, size)].setAlive(true);
  grid.data[setter(15, 11, width, size)].setAlive(true);

  grid.data[setter(19, 11, width, size)].setAlive(true);
  grid.data[setter(20, 11, width, size)].setAlive(true);
  grid.data[setter(21, 11, width, size)].setAlive(true);

  grid.data[setter(11, 13, width, size)].setAlive(true);
  grid.data[setter(16, 13, width, size)].setAlive(true);

  grid.data[setter(18, 13, width, size)].setAlive(true);
  grid.data[setter(23, 13, width, size)].setAlive(true);

  grid.data[setter(11, 14, width, size)].setAlive(true);
  grid.data[setter(16, 14, width, size)].setAlive(true);

  grid.data[setter(18, 14, width, size)].setAlive(true);
  grid.data[setter(23, 14, width, size)].setAlive(true);

  grid.data[setter(11, 15, width, size)].setAlive(true);
  grid.data[setter(16, 15, width, size)].setAlive(true);

  grid.data[setter(18, 15, width, size)].setAlive(true);
  grid.data[setter(23, 15, width, size)].setAlive(true);

  grid.data[setter(13, 16, width, size)].setAlive(true);
  grid.data[setter(14, 16, width, size)].setAlive(true);
  grid.data[setter(15, 16, width, size)].setAlive(true);

  grid.data[setter(19, 16, width, size)].setAlive(true);
  grid.data[setter(20, 16, width, size)].setAlive(true);
  grid.data[setter(21, 16, width, size)].setAlive(true);

  //////////////////////////////////////////////////////

  grid.data[setter(13, 18, width, size)].setAlive(true);
  grid.data[setter(14, 18, width, size)].setAlive(true);
  grid.data[setter(15, 18, width, size)].setAlive(true);

  grid.data[setter(19, 18, width, size)].setAlive(true);
  grid.data[setter(20, 18, width, size)].setAlive(true);
  grid.data[setter(21, 18, width, size)].setAlive(true);

  grid.data[setter(11, 19, width, size)].setAlive(true);
  grid.data[setter(16, 19, width, size)].setAlive(true);

  grid.data[setter(18, 19, width, size)].setAlive(true);
  grid.data[setter(23, 19, width, size)].setAlive(true);

  grid.data[setter(11, 20, width, size)].setAlive(true);
  grid.data[setter(16, 20, width, size)].setAlive(true);

  grid.data[setter(18, 20, width, size)].setAlive(true);
  grid.data[setter(23, 20, width, size)].setAlive(true);

  grid.data[setter(11, 21, width, size)].setAlive(true);
  grid.data[setter(16, 21, width, size)].setAlive(true);

  grid.data[setter(18, 21, width, size)].setAlive(true);
  grid.data[setter(23, 21, width, size)].setAlive(true);

  grid.data[setter(13, 23, width, size)].setAlive(true);
  grid.data[setter(14, 23, width, size)].setAlive(true);
  grid.data[setter(15, 23, width, size)].setAlive(true);

  grid.data[setter(19, 23, width, size)].setAlive(true);
  grid.data[setter(20, 23, width, size)].setAlive(true);
  grid.data[setter(21, 23, width, size)].setAlive(true);

  grid.play();
}