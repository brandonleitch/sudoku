#ifndef GRID_H
#define GRID_H

#include <string>

class Grid {
private:
  std::string puzzle;
  std::string solution;
  char grid[9][9];
  bool check_cell(int row, int col);

public:
  Grid(std::string p, std::string s);
  void init();

  void set(int row, int col, char num);
  int get(int row, int col);
  bool is_puzzle_cell(int row, int col);
  bool check();
};


#endif
