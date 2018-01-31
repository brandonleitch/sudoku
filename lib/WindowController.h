#ifndef WINDOW_CONTROLLER_H
#define WINDOW_CONTROLLER_H

#include <ncurses.h>
#include <vector>
#include "Grid.h"

class WindowController{
public:
  static std::vector< std::vector<WINDOW*> > windows;

  static void gen_windows();

  static void fill_screen_border();

  static void fill_char_at(WINDOW *win, int row, int col, char c);

  static void fill_window(WINDOW *win, int y, int x, Grid g);
  static void fill_border(WINDOW *win);

  static void fill_all_windows(Grid g);
  static void fill_all_borders();

  static void refresh_window(WINDOW *win);
  static void refresh_all_windows();

  static void delete_window(WINDOW *win);
  static void delete_all_windows();

  static void highlight(int row, int col);
};


#endif
