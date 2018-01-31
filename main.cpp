#include <ncurses.h>
#include "lib/WindowController.h"
#include "lib/InputController.h"
#include "lib/Grid.h"

void move(Direction d);

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

  // Create and fill all windows
  WindowController::gen_windows();
  WindowController::fill_screen_border();
  WindowController::fill_all_windows();
  WindowController::fill_all_borders();

  WindowController::highlight(y,x);
  WindowController::refresh_all_windows();

  Grid grid;
  grid.init();

  while(true) {

    char ch = InputController::get_char();

    if(InputController::get_action(ch) == MOVE) {

      Direction dir = InputController::get_dir(ch);
      move(dir);

    }

    if(InputController::get_action(ch) == NUM) {

      grid.set(y,x,ch);

    }

    WindowController::fill_all_windows();
    WindowController::highlight(y,x);
    WindowController::refresh_all_windows();
  }





  // Wait for user input to end
  getch();


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
