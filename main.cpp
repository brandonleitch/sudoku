#include <ncurses.h>
#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "lib/WindowController.h"
#include "lib/InputController.h"
#include "lib/Grid.h"

void move(Direction d);

void menu_action(MenuAction m, Grid* g);

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

  std::fstream puzzle_file;
  puzzle_file.open("puzzles/sudoku.csv");

  std::string puzzle;
  std::string solution;

  std::string buffer;

  // Set seed to current time and pick random puzzle
  srand (time (NULL));
  for(int i = 0; i < rand() % 100; i++) {
    getline(puzzle_file, buffer);
  }

  getline(puzzle_file, puzzle, ',');
  getline(puzzle_file, solution);

  // Init grid
  Grid grid(puzzle, solution);
  grid.init();

  // Create and fill all windows
  WindowController::gen_windows();
  WindowController::fill_screen_border();
  WindowController::fill_all_windows(grid);
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

      grid.set(y,x,ch);

    }

    if(InputController::get_action(ch) == MENU) {

      MenuAction m = InputController::get_menu_action(ch);

      if(m == QUIT) {
        break;
      }

      menu_action(m, &grid);

    }

    WindowController::fill_all_windows(grid);
    WindowController::highlight(y,x);
    WindowController::refresh_all_windows();

    if(grid.check()) {
      break;
    }
  }

  // Clear mem from windows
  WindowController::delete_all_windows();

  endwin();
  return 0;
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

void menu_action(MenuAction m, Grid* g) {
  switch (m) {
    case CLEAR: g->init();
  }
}
