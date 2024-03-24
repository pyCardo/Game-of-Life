#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cassert>
#include <thread>
#include <vector>

namespace constants {
auto const COLOR_DEAD = sf::Color::Black;
auto const COLOR_ALIVE = sf::Color::White;
auto const COLOR_BOUND = sf::Color(66, 71, 76, 255);  // RGBA Gray
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
  int width_;
  int height_;
  int cellSize_;
  int rows_;
  int columns_;
  bool isPlaying_{true};

 public:
  std::vector<Cell> data;
  int dataSize;
  sf::RectangleShape square;

  Board(int w, int h, int cs) : width_{w}, height_{h}, cellSize_{cs} {
    assert(w > 0 && h > 0 && cellSize_ > 0);
    assert(w % cellSize_ == 0 && h % cellSize_ == 0);

    rows_ = h / cellSize_;
    columns_ = w / cellSize_;

    data = std::vector<Cell>(rows_ * columns_);
    dataSize = static_cast<int>(data.size());

    square.setSize(sf::Vector2f(cellSize_ - 1, cellSize_ - 1));
    square.setOutlineThickness(1);
    square.setOutlineColor(constants::COLOR_BOUND);
  };

  void paint(sf::RenderWindow&, int, int, bool);
  void play();
};

void Board::paint(sf::RenderWindow& window, int c, int r, bool alive) {
  assert(c >= 0 && c < columns_);
  assert(r >= 0 && r < rows_);

  square.setPosition(c * cellSize_, r * cellSize_);
  if (alive) {
    square.setFillColor(constants::COLOR_ALIVE);
  } else {
    square.setFillColor(constants::COLOR_DEAD);
  }
  window.draw(square);
}

void Board::play() {
  sf::RenderWindow window(sf::VideoMode(width_, height_), "Game of Life");
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Event event;

  // generate first board
  for (int i{0}; i < dataSize; i++) {
    int x{i % columns_};
    int y{i / columns_};
    if (data[i].getAlive()) {
      paint(window, x, y, true);
    } else {
      paint(window, x, y, false);
    }
  }

  window.setFramerateLimit(30);

  // game loop
  while (window.isOpen()) {
    // event handling
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::Space) {
            isPlaying_ = !isPlaying_;
          }
          break;
        default:
          break;
      }
    }

    window.display();

    if (isPlaying_) {
      // generate the next board
      for (int i{0}; i < dataSize; i++) {
        int x{i % columns_};
        int y{i / columns_};
        assert(x + y * columns_ == i);

        data[i].nextAlive = data[i].update(data, x, y, columns_);

        if (data[i].getAlive() !=
            data[i].nextAlive) {  // it only paints the cell
                                  // if it's been modified
          paint(window, x, y, data[i].nextAlive);
        }
      }
      // refresh the board
      for (int i{0}; i < dataSize; i++) {
        data[i].setAlive(data[i].nextAlive);
      }
    }
  }
}

int setter(int x, int y, int const width, int const size) {
  return x + y * width / size;
}