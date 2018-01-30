#include <ncurses.h>


#define HEIGHT 5
#define WIDTH 17

#define MAX_HEIGHT HEIGHT * 3 + 4
#define MAX_WIDTH WIDTH * 3 + 4

#define NUM_WINDOW_ROWS
#define NUM_WINDOW_COLS

class WindowController {
public:
  static WINDOW* windows[3][3];
  static void gen_windows();
  static void fill_screen_delims();
  static void fill_window(WINDOW *win);
  static void fill_delims(WINDOW *win);
  static int get_row(int r);
  static int get_col(int c);
  static void fill_all_windows();
  static void fill_all_delims();
};




int main() {

  // Initialize curses screen
  initscr();

  //Don't print typed characters
  noecho();

  //Disable line buffering, pass characters immediately to curses
  cbreak();

  refresh();

  WindowController::fill_screen_delims();


  // WINDOW *windows = gen_windows();
  WindowController::gen_windows();


  // Wait for user input to end
  getch();

  // Delete all windows
  // for(int i = 0; i < NUM_WINDOWS; i++) {
  //   delwin(windows[i]);
  // }

  endwin();
  return 0;
}

void WindowController::gen_windows() {

  int row_counter = 0;
  int col_counter = 0;

  for(int r = 1; r < MAX_HEIGHT; r+=6) {
    for(int c = 1; c < MAX_WIDTH; c+=18) {
      // Create a new window at current location
      WINDOW *w = newwin(HEIGHT, WIDTH, r, c);
      // fill_window(w);
      // fill_delims(w);
      windows[row_counter][col_counter++] = w;

    }
    row_counter++;
  }

  // return windows;
}

void WindowController::fill_screen_delims() {

  // Turn on bold
  attron(A_BOLD);

  // Fill  walls
  for(int r = 1; r < MAX_HEIGHT; r+=2) {
    for(int c = 0; c < MAX_WIDTH; c+= WIDTH + 1)
      mvaddch(r, c, '|');
  }

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

void WindowController::fill_window(WINDOW *win) {

  // Turn on bold
  wattron(win, A_REVERSE);

  // Fill window with blank dots
  for(int r = 0; r < HEIGHT; r+=2) {
    for(int c = 2; c < WIDTH; c+=6)
      mvwaddch(win, r, c, ' ');
  }


  // Turn off bold
  wattroff(win, A_REVERSE);

  // Refresh current window to screen
  wrefresh(win);
}

void WindowController::fill_delims(WINDOW *win) {

  // Fill windows with walls
  for(int r = 0; r < HEIGHT; r+=2) {
    for(int c = 5; c < WIDTH; c+=6)
      mvwaddch(win, r, c, '|');
  }

  // Fill floors
  for(int r = 1; r < HEIGHT; r+=2) {
    mvwaddstr(win, r, 0, "-----+-----+-----");
  }

  // Refresh current window to screen
  wrefresh(win);
}

void WindowController::fill_all_windows() {

}

void WindowController::fill_all_delims() {

}

int WindowController::get_row(int r) {

}

int WindowController::get_col(int c) {

}
