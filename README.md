# Game of Life in C++
Risorse del progetto:
- Wikipedia [_Conway's Game of Life_](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).
~~~bash
$ g++ gameOfLife.cpp -Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system
$ export DISPLAY=:0
$ export DISPLAY="$(/sbin/ip route | awk '/default/ { print $3 }'):0"
$ export LIBGL_ALWAYS_INDIRECT=0
~~~
Execute inside GUI (MobaXterm).
NOTE: add time and population counters.