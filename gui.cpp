#include <ncurses.h>
#include <vector>

#define HEIGHT 5
#define WIDTH 17

#define MAX_HEIGHT HEIGHT * 3 + 4
#define MAX_WIDTH WIDTH * 3 + 4

#define NUM_WINDOW_ROWS 3
#define NUM_WINDOW_COLS 3


class WindowController {
public:
  static std::vector< std::vector<WINDOW*> > windows;
  static void gen_windows();
  static void fill_screen_border();
  static void fill_window(WINDOW *win);
  static void fill_border(WINDOW *win);
  static int get_row(int r);
  static int get_col(int c);
  static void fill_all_windows();
  static void fill_all_borders();
  static void delete_window(WINDOW *win);
  static void delete_all_windows();
};

std::vector< std::vector<WINDOW*> > WindowController::windows;




int main() {

  // Initialize curses screen
  initscr();

  //Don't print typed characters
  noecho();

  //Disable line buffering, pass characters immediately to curses
  cbreak();

  refresh();

  // Create and fill all windows
  WindowController::gen_windows();
  WindowController::fill_screen_border();
  WindowController::fill_all_windows();
  WindowController::fill_all_borders();



  // Wait for user input to end
  getch();


  // Clear mem from windows
  WindowController::delete_all_windows();

  endwin();
  return 0;
}

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

  // Refresh current window to screen
  wrefresh(win);
}

void WindowController::delete_window(WINDOW *win) {
  delwin(win);
}

void WindowController::fill_all_windows() {

  for(int i = 0; i < NUM_WINDOW_ROWS; i++) {
    for(int j = 0; j < NUM_WINDOW_COLS; j++) {
      fill_window(windows[i][j]);
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

void WindowController::delete_all_windows() {
  for(int i = 0; i < NUM_WINDOW_ROWS; i++) {
    for(int j = 0; j < NUM_WINDOW_COLS; j++) {
      delete_window(windows[i][j]);
    }
  }
}

int WindowController::get_row(int r) {

}

int WindowController::get_col(int c) {

}
