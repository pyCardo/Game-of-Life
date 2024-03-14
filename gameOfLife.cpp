#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
// #include <iostream>
// #include <string>

// #include "doctest.h"
// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

class Cell {
  bool isAlive_{false};

 public:
  bool nextAlive;
  void setAlive(bool S) { isAlive_ = S; }
  bool update(std::vector<Cell>, int, int, int);
};

bool Cell::update(std::vector<Cell> data, int xIndex, int yIndex, int rowSize) {
  int neighbours{};
  for (int x{xIndex - 1}; x <= xIndex + 1; x++) {
    for (int y{yIndex - 1}; y <= yIndex + 1; y++) {
      if (x < 0 || y < 0 || x >= rowSize ||
          y >= (static_cast<int>(data.size()) / rowSize))
        continue;  // skip the elements outside of the border
      if (x == xIndex && y == yIndex) {
        continue;
      }
      if (data[x + y * rowSize].isAlive_) {
        neighbours++;
      }
    }
  }
  // std::cout << neighbours << '\n';
  // assert(neighbours >= 0 && neighbours <= 2);  // this assert is failing

  if (isAlive_) {
    if (neighbours == 2 || neighbours == 3) return true;
  } else {
    if (neighbours == 3) return true;
  }
  return false;
}

class Grid {
  sf::Image image_;
  int width_;
  int height_;
  int cellSize_;
  int rows_;
  int columns_;

 public:
  std::vector<Cell> data;
  Grid(int w, int h, int cs) : width_{w}, height_{h}, cellSize_{cs} {
    assert(w > 0 && h > 0 && cellSize_ > 0);
    assert(w % cellSize_ == 0 && h % cellSize_ == 0);
    rows_ = h / cellSize_;
    columns_ = w / cellSize_;
    image_.create(w, h, sf::Color::Black);
    data = std::vector<Cell>(rows_ * columns_);
  };

  void draw(int, int, bool);
  void cancel(int, int);
  void play();
};

void Grid::draw(int c, int r, bool color) {
  assert(c >= 0 && c < columns_);
  assert(r >= 0 && r < rows_);

  for (int i{c * cellSize_}; i < (c + 1) * cellSize_; i++) {
    for (int j{r * cellSize_}; j < (r + 1) * cellSize_; j++) {
      if (color) {
        image_.setPixel(i, j, sf::Color::White);
      } else {
        image_.setPixel(i, j, sf::Color::Black);
      }
    }
  }
}

void Grid::play() {
  sf::RenderWindow window(sf::VideoMode(width_, height_), "Game of Life");
  window.setFramerateLimit(3);
  sf::Texture texture;
  sf::Sprite sprite;

  texture.loadFromImage(image_);

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    for (int i{0}; i < static_cast<int>(data.size()); i++) {
      int x{i % columns_};
      int y{i / columns_};
      assert(x + y * columns_ == i);
      data[i].nextAlive = data[i].update(data, x, y, columns_);
      // assert(data[i].nextAlive == false);
      draw(x, y, data[i].nextAlive);
    }

    for (int i{0}; i < static_cast<int>(data.size()); i++) {
      data[i].setAlive(data[i].nextAlive);
    }

    texture.update(image_);
    sprite.setTexture(texture);

    window.clear();
    window.draw(sprite);
    window.display();
  }
}

int setter(int x, int y, int const width, int const size){
  return x+y*width/size;
}

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

  /////////////////////////////////////////////////////////

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

// TEST_CASE("Cell::update testing") {
//   int const width{800};
//   int const height{800};
//   int const size{40};

//   Grid grid{width, height, size};
//   grid.data[83].setAlive(true);
//   grid.data[84].setAlive(true);
//   grid.data[85].setAlive(true);

//   CHECK(grid.data[83].update(grid.data, 4, 4, 20) == false);
//   CHECK(grid.data[83].update(grid.data, 4, 4, 20) == false);
//   CHECK(grid.data[83].update(grid.data, 4, 4, 20) == false);
// }