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
  if(!is_puzzle_cell(row, col))
    grid[row][col] = num;
}

int Grid::get(int row, int col) {
  return grid[row][col];
}

bool Grid::is_puzzle_cell(int row, int col) {
  char c = puzzle.at(row * 9 + col);
  return c != '0';
}

bool Grid::check() {
  for (int i = 0; i < 9; i++) {
    for(int j = 0; j < 9; j++) {
      if(!check_cell(i, j)) {
        return false;
      }
    }
  }
  return true;
}

bool Grid::check_cell(int row, int col) {
  return get(row, col) == solution.at(row * 9 + col);
}
