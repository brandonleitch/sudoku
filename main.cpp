#include <ncurses.h>
#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "lib/WindowController.h"
#include "lib/InputController.h"
#include "lib/Grid.h"

void move(Direction d);

void menu_action(MenuAction m, Grid** g, int* n);

Grid* start_puzzle(int n);

int x = 0;
int y = 0;

int main() {

  // Initialize curses screen
  initscr();

  //Don't print typed characters
  noecho();

  //Disable line buffering, pass characters immediately to curses
  cbreak();

  // Hide cursor
  curs_set(0);

  refresh();


  // Set seed to time
  srand(time(NULL));

  // Get random puzzle
  int n = rand() % 100;
  Grid* grid = start_puzzle(n);

  // Create and fill all windows
  WindowController::gen_windows();
  WindowController::fill_screen_border();
  WindowController::fill_all_windows(*grid);
  WindowController::fill_all_borders();

  WindowController::highlight(y,x);
  WindowController::refresh_all_windows();


  while(true) {

    char ch = InputController::get_char();

    if(InputController::get_action(ch) == MOVE) {

      Direction dir = InputController::get_dir(ch);
      move(dir);

    }

    if(InputController::get_action(ch) == NUM) {

      grid->set(y,x,ch);

    }

    if(InputController::get_action(ch) == MENU) {

      MenuAction m = InputController::get_menu_action(ch);

      if(m == QUIT) {
        break;
      }

      menu_action(m, &grid, &n);

    }

    WindowController::fill_all_windows(*grid);
    WindowController::highlight(y,x);
    WindowController::refresh_all_windows();

    if(grid->check()) {
      break;
    }
  }

  // Clear mem from windows
  WindowController::delete_all_windows();

  endwin();
  return 0;
}

Grid* start_puzzle(int n) {

  std::fstream puzzle_file;
  puzzle_file.open("puzzles/sudoku.csv");

  std::string puzzle;
  std::string solution;

  std::string buffer;

  // Skip lines
  for(int i = 0; i < n; i++) {
    getline(puzzle_file, buffer);
  }

  getline(puzzle_file, puzzle, ',');
  getline(puzzle_file, solution);

  // Init grid
  Grid* grid = new Grid(puzzle, solution);
  grid->init();

  return grid;
}


void move(Direction d) {
  switch(d) {
    case DOWN: y = (++y + 9) % 9;
      break;
    case UP: y = (--y + 9) % 9;
      break;
    case RIGHT: x = (++x + 9) % 9;
      break;
    case LEFT: x = (--x + 9) % 9;
      break;
  }
}

void menu_action(MenuAction m, Grid** g, int* n) {
  switch (m) {
    case CLEAR: (*g)->init(); break;
    case PREV:
      *n = (--(*n) + 100) % 100;
      *g = start_puzzle(*n) ;
      break;
    case NEXT:
      *n = (++(*n) + 100) % 100;
      *g = start_puzzle(*n) ;
      break;
  }
}
