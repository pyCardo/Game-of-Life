#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cassert>
#include <thread>
#include <vector>

namespace constants {
  auto const COLOR_DEAD = sf::Color::Black;
  auto const COLOR_ALIVE = sf::Color::White;
}

class Cell {
  bool isAlive_{false};

 public:
  bool nextAlive;
  bool getAlive() { return isAlive_; };
  void setAlive(bool S) { isAlive_ = S; }
  bool update(std::vector<Cell> const&, int, int, int);
};

bool Cell::update(std::vector<Cell> const& data, int xIndex, int yIndex, int rowSize) {
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

  if (isAlive_) {
    if (neighbours == 2 || neighbours == 3) return true;
  } else {
    if (neighbours == 3) return true;
  }
  return false;
}

class Board {
  sf::Image image_;
  int width_;
  int height_;
  int cellSize_;
  int rows_;
  int columns_;

 public:
  std::vector<Cell> data;

  Board(int w, int h, int cs) : width_{w}, height_{h}, cellSize_{cs} {
    assert(w > 0 && h > 0 && cellSize_ > 0);
    assert(w % cellSize_ == 0 && h % cellSize_ == 0);

    rows_ = h / cellSize_;
    columns_ = w / cellSize_;
    image_.create(w, h, constants::COLOR_DEAD);
    data = std::vector<Cell>(rows_ * columns_);
  };

  void draw(int, int, bool);
  void play();
};

void Board::draw(int c, int r, bool alive) {
  assert(c >= 0 && c < columns_);
  assert(r >= 0 && r < rows_);

  for (int i{c * cellSize_}; i < (c + 1) * cellSize_; i++) {
    for (int j{r * cellSize_}; j < (r + 1) * cellSize_; j++) {
      if (alive) {
        image_.setPixel(i, j, constants::COLOR_ALIVE);
      } else {
        image_.setPixel(i, j, constants::COLOR_DEAD);
      }
    }
  }
}

void Board::play() {
  sf::RenderWindow window(sf::VideoMode(width_, height_), "Game of Life");
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Event event;

  texture.loadFromImage(image_);
  window.setFramerateLimit(30);

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    // generate the new board
    for (int i{0}; i < static_cast<int>(data.size()); i++) {
      int x{i % columns_};
      int y{i / columns_};
      assert(x + y * columns_ == i);

      data[i].nextAlive = data[i].update(data, x, y, columns_);

      if (data[i].getAlive() !=
          data[i].nextAlive) {  // it only draws the cell if it's been modified
        draw(x, y, data[i].nextAlive);
      }
    }

    // refresh the board
    for (int i{0}; i < static_cast<int>(data.size()); i++) {
      data[i].setAlive(data[i].nextAlive);
    }

    texture.update(image_);
    sprite.setTexture(texture);
    window.draw(sprite);
    window.display();
  }
}

int setter(int x, int y, int const width, int const size) {
  return x + y * width / size;
}