#include "Grid.h"

void Grid::init(){
  for(int i = 0; i < 9; i++) {
    for(int j = 0; j < 9; j++) {
      set(i, j, ' ');
    }
  }
}

void Grid::set(int row, int col, char num) {
  grid[row][col] = num;
}

int Grid::get(int row, int col) {
  return grid[row][col];
}
