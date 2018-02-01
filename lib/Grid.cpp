#include "Grid.h"


Grid::Grid(std::string p, std::string s){
  this->puzzle = p;
  this->solution = s;
}

void Grid::init(){
  for(int i = 0; i < 9; i++) {
    for(int j = 0; j < 9; j++) {
      char c = puzzle.at(i * 9 + j);
      if (c == '0') {
        set(i, j, ' ');
      }
      else {
        grid[i][j] = c;
      }
    }
  }
}

void Grid::set(int row, int col, char num) {
  char c = puzzle.at(row * 9 + col);
  if (c == '0')
    grid[row][col] = num;
}

int Grid::get(int row, int col) {
  return grid[row][col];
}
