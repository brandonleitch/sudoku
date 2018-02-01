# Sudoku

Plays sudoku in terminal

### Prereqs

ncurses library https://www.gnu.org/software/ncurses/

```
sudo apt-get install libncurses5-dev
```

### Compilation

```
g++ main.cpp lib/*.cpp -lncurses -o filename
```

### Playing

Use WASD to navigate board  
Press a number key (1-9) on a highlighted cell to input it  
Press "q" to quit  
Press "c" to clear the current puzzle  
Press "," or "." to change to the previous and following puzzles
