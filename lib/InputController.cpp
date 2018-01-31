#include "InputController.h"

char InputController::MOVE_CHARS[NUM_MOVE_CHARS] = {'w','a','s','d'};
char InputController::NUM_CHARS[NUM_NUM_CHARS] = {'1','2','3','4','5','6','7','8','9'};

char InputController::get_char() {
  char ch = getch();
  while(!valid_char(ch)){
    ch = getch();
  }
  return ch;
}

Direction InputController::get_dir(char c) {

  switch(c) {

    case 's': return DOWN;
      break;
    case 'w': return UP;
      break;

    case 'd': return RIGHT;
      break;
    case 'a': return LEFT;
      break;
  }

}

Action InputController::get_action(char c) {
  if(is_move_char(c)) {
    return MOVE;
  }

  if(is_num_char(c)) {
    return NUM;
  }
}

bool InputController::valid_char(char c) {
  return is_move_char(c) || is_num_char(c);
}

bool InputController::is_move_char(char c) {
  for(int i = 0; i < NUM_MOVE_CHARS; i++) {
    if(c == MOVE_CHARS[i]) {
      return true;
    }
  }
  return false;
}

bool InputController::is_num_char(char c) {
  for(int i = 0; i < NUM_NUM_CHARS; i++) {
    if(c == NUM_CHARS[i]) {
      return true;
    }
  }
  return false;
}
