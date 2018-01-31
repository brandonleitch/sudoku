#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <ncurses.h>

#define NUM_MOVE_CHARS 4
#define NUM_NUM_CHARS 9
#define NUM_MENU_CHARS 1

enum Direction {
  LEFT, RIGHT, UP, DOWN
};

enum MenuAction {
  CLEAR
};

enum Action {
  MOVE, NUM, MENU
};

class InputController {
private:
  static char MOVE_CHARS[NUM_MOVE_CHARS];
  static char NUM_CHARS[NUM_NUM_CHARS];
  static char MENU_CHARS[NUM_MENU_CHARS];
  static bool valid_key(char c);

public:
  static char get_char();
  static Direction get_dir(char c);
  static MenuAction get_menu_action(char c);
  static Action get_action(char c);
  static bool valid_char(char c);
  static bool is_move_char(char c);
  static bool is_num_char(char c);
  static bool is_menu_char(char c);
};

#endif
