#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cassert>
#include <chrono>
#include <thread>
#include <vector>
// #include <iostream>
// #include <string>

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
      if (x == xIndex && y == yIndex) continue;
      if (data[xIndex + yIndex * rowSize].isAlive_) neighbours++;
    }
  }

  if (isAlive_) {
    if (neighbours == 2 || neighbours == 3) return true;
  } else {
    if (neighbours == 3) return true;
  }
  return false;
}

class Grid {
  sf::Image image_;
  int cellSize_;
  int rows_;
  int columns_;
  int width_;
  int height_;
  std::vector<Cell> data;

 public:
  Grid(int w, int h, int cs) : width_{w}, height_{h}, cellSize_{cs} {
    assert(w > 0 && h > 0 && cellSize_ > 0);
    assert(w % cellSize_ == 0 && h % cellSize_ == 0);
    rows_ = h / cellSize_;
    columns_ = w / cellSize_;
    image_.create(w, h, sf::Color::White);
    data = std::vector<Cell>(rows_ * columns_);
  };

  void draw(int, int);
  void play();
};

void Grid::draw(int c, int r) {
  assert(c >= 0 && c < columns_);
  assert(r >= 0 && r < rows_);

  for (int i{c * cellSize_}; i < (c + 1) * cellSize_; i++) {
    for (int j{r * cellSize_}; j < (r + 1) * cellSize_; j++) {
      image_.setPixel(i, j, sf::Color::Black);
    }
  }
}

void Grid::play() {
  sf::RenderWindow window(sf::VideoMode(width_, height_), "Game of Life");
  assert(1==0);
  window.setFramerateLimit(60);
  sf::Texture texture;
  texture.loadFromImage(image_);
  sf::Sprite sprite;
  sprite.setTexture(texture);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    for (int i{0}; i < data.size(); i++) {
      int x{i / columns_};
      int y{i % columns_};
      assert(x + y * columns_ <= i);
      data[i].nextAlive = data[i].update(data, x, y, columns_);
      if (data[i].nextAlive) draw(x, y);
    }

    for (int i{0}; i < data.size(); i++) {
      data[i].setAlive(data[i].nextAlive);
    }

    texture.update(image_);

    window.clear();
    window.draw(sprite);
    window.display();
  }
}

int main() {
  int const width{600};
  int const height{600};
  int const size{10};
  Grid grid{width, height, size};
  grid.play();
}

// compile --> g++ gameOfLife.cpp -lsfml-graphics -lsfml-window -lsfml-system