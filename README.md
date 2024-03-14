# Game of Life in C++
## Project resources
- Wikipedia: [_Conway's Game of Life_](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)
- [LifeWiki](https://conwaylife.com/wiki/Main_Page)
## How to
Compile using:
~~~bash
$ g++ name.cpp -Wall -Wextra -DNDEBUG -lsfml-graphics -lsfml-window -lsfml-system
~~~
To set your screen on WSL:
~~~bash
$ export DISPLAY=:0
~~~
## Instructions before committing!
- Do **not** commit the output file
## Next up: Issues & Features
1) Add time and population counters
2) Reduce algorithm complexity
3) Try implementing a 2D vector