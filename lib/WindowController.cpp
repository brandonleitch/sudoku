#include "WindowController.h"

#define HEIGHT 5
#define WIDTH 17

#define MAX_HEIGHT HEIGHT * 3 + 4
#define MAX_WIDTH WIDTH * 3 + 4

#define NUM_WINDOW_ROWS 3
#define NUM_WINDOW_COLS 3

std::vector< std::vector<WINDOW*> > WindowController::windows;

void WindowController::gen_windows() {


  for(int r = 1; r < MAX_HEIGHT; r+=6) {


    std::vector<WINDOW*> wins;

    for(int c = 1; c < MAX_WIDTH; c+=18) {

      // Create a new window at current location
      WINDOW *w = newwin(HEIGHT, WIDTH, r, c);

      // Add window to windows array
      wins.push_back(w);
    }

    WindowController::windows.push_back(wins);
  }

}

void WindowController::fill_screen_border() {

  // Turn on bold
  attron(A_BOLD);

  // Fill  walls
  for(int r = 1; r < MAX_HEIGHT; r+=2) {
    for(int c = 0; c < MAX_WIDTH; c+= WIDTH + 1)
      mvaddch(r, c, '|');
  }

  // Fill corners
  for(int r = 0; r < MAX_HEIGHT; r+=2) {
    for(int c = 0; c < MAX_WIDTH; c+= WIDTH + 1)
      mvaddch(r, c, '+');
  }

  // Fill floors
  for(int r = 0; r < MAX_HEIGHT; r+= HEIGHT + 1) {
    mvaddstr(r, 0, "+-----+-----+-----+-----+-----+-----+-----+-----+-----+");
  }


  // Turn off bold
  attroff(A_BOLD);
  refresh();
}

void WindowController::fill_window(WINDOW *win, int y, int x, Grid g) {

  // Fill window with blanks
  for(int r = 0; r < 3; r++) {
    for(int c = 0; c < 3; c++)
      fill_char_at(win, r, c, g.get(y * 3 + r, x * 3 + c));
  }

}

void WindowController::fill_border(WINDOW *win) {
  // Fill windows with walls
  for(int r = 0; r < HEIGHT; r+=2) {
    for(int c = 5; c < WIDTH; c+=6)
      mvwaddch(win, r, c, '|');
  }

  // Fill floors
  for(int r = 1; r < HEIGHT; r+=2) {
    mvwaddstr(win, r, 0, "-----+-----+-----");
  }

}

void WindowController::delete_window(WINDOW *win) {
  delwin(win);
}

void WindowController::delete_all_windows() {
  for(int i = 0; i < NUM_WINDOW_ROWS; i++) {
    for(int j = 0; j < NUM_WINDOW_COLS; j++) {
      delete_window(windows[i][j]);
    }
  }
}

void WindowController::fill_all_windows(Grid g) {

  for(int i = 0; i < NUM_WINDOW_ROWS; i++) {
    for(int j = 0; j < NUM_WINDOW_COLS; j++) {
      fill_window(windows[i][j], i, j, g);
    }
  }

}

void WindowController::fill_all_borders() {
  for(int i = 0; i < NUM_WINDOW_ROWS; i++) {
    for(int j = 0; j < NUM_WINDOW_COLS; j++) {
      fill_border(windows[i][j]);
    }
  }
}

void WindowController::refresh_window(WINDOW* win) {
  wrefresh(win);
}

void WindowController::refresh_all_windows(){
  for(int i = 0; i < NUM_WINDOW_ROWS; i++) {
    for(int j = 0; j < NUM_WINDOW_COLS; j++) {
      refresh_window(windows[i][j]);
    }
  }
}

void WindowController::highlight(int row, int col) {
  WINDOW* win = windows.at(row / 3).at(col / 3);
  wattron(win, A_REVERSE);
  fill_char_at(win, row % 3, col % 3, ' ');
  wattroff(win, A_REVERSE);
}

void WindowController::fill_char_at(WINDOW *win, int row, int col, char c) {
  mvwaddch(win, row * 2, col * 6 + 2, c);
}
