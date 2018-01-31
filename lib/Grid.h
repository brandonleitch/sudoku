#ifndef GRID_H
#define GRID_H

class Grid {
private:
  char grid[9][9];

public:
  void init();

  void set(int row, int col, char num);
  int get(int row, int col);
};


#endif
