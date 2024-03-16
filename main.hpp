#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cassert>
#include <thread>
#include <vector>

namespace constants {
auto const COLOR_DEAD = sf::Color::Black;
auto const COLOR_ALIVE = sf::Color::White;
auto const OFFSETS = std::vector<std::pair<int, int>>{
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
}  // namespace constants

class Cell {
  bool isAlive_{false};

 public:
  bool nextAlive;
  bool getAlive() { return isAlive_; };
  void setAlive(bool S) { isAlive_ = S; }
  bool update(std::vector<Cell> const&, int, int, int);
};

bool Cell::update(std::vector<Cell> const& data, int xIndex, int yIndex,
                  int rowSize) {
  int neighbors{};

  for (const auto& offset : constants::OFFSETS) {
    int x = xIndex + offset.first;
    int y = yIndex + offset.second;

    // check if the neighbor is within the bounds of the grid
    if (x >= 0 && x < rowSize && y >= 0 &&
        y < static_cast<int>(data.size()) / rowSize) {
      if (data[x + y * rowSize].isAlive_) {
        neighbors++;
      }
    }
  }

  if (isAlive_) {
    if (neighbors == 2 || neighbors == 3) return true;
  } else {
    if (neighbors == 3) return true;
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
  // sf::RectangleShape livingCell;
  // sf::RectangleShape deadCell;

  Board(int w, int h, int cs) : width_{w}, height_{h}, cellSize_{cs} {
    assert(w > 0 && h > 0 && cellSize_ > 0);
    assert(w % cellSize_ == 0 && h % cellSize_ == 0);

    rows_ = h / cellSize_;
    columns_ = w / cellSize_;
    image_.create(w, h, constants::COLOR_DEAD);
    data = std::vector<Cell>(rows_ * columns_);

    // livingCell.setSize(sf::Vector2f(cellSize_, cellSize_));
    // livingCell.setFillColor(constants::COLOR_ALIVE);
    // deadCell.setSize(sf::Vector2f(cellSize_, cellSize_));
    // livingCell.setFillColor(constants::COLOR_DEAD);
  };

  void paint(int, int, bool);
  void play();
};

void Board::paint(int c, int r, bool alive) {
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

  // generate first board
  for (int i{0}; i < static_cast<int>(data.size()); i++) {
    int x{i % columns_};
    int y{i / columns_};
    if (data[i].getAlive()) {
      paint(x, y, true);
    }
  }

  texture.loadFromImage(image_);
  window.setFramerateLimit(30);

  // game loop
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    // draw current board
    texture.update(image_);
    sprite.setTexture(texture);
    window.draw(sprite);
    window.display();

    // generate the next board
    for (int i{0}; i < static_cast<int>(data.size()); i++) {
      int x{i % columns_};
      int y{i / columns_};
      assert(x + y * columns_ == i);

      data[i].nextAlive = data[i].update(data, x, y, columns_);

      if (data[i].getAlive() !=
          data[i].nextAlive) {  // it only paints the cell if it's been modified
        paint(x, y, data[i].nextAlive);
      }
    }

    // refresh the board
    for (int i{0}; i < static_cast<int>(data.size()); i++) {
      data[i].setAlive(data[i].nextAlive);
    }
  }
}

int setter(int x, int y, int const width, int const size) {
  return x + y * width / size;
}