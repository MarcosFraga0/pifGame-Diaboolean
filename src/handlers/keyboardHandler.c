/**
 * @file keyboardHandler.c
 * @date Nov, 10th 2025
 * @brief generic handlers
 */

#include <ctype.h>
#include "handlers/keyboardHandler.h"

/**
 * @brief handler of user actions
 */
Action keyboardActionHandler(char ch){
  Action action = actionNone;
  switch (tolower(ch))
  {
  case 'v':
    action = setTrue;
    break;
  case 'f':
    action = setFalse;
    break;
  case 'r':
    action = reset;
    break;
  default:
    break;
  }

  return action;
}

/**
 * @brief handler of entity velocity
 */
Vector2D keyboardVelHandler(char ch, int step) {
  Vector2D vel = {0, 0};
  switch (tolower(ch)) {
  case 'w':
    vel.y = -1 * step / 2;
    break;
  case 's':
    vel.y = 1 * step / 2;
    break;
  case 'a':
    vel.x = -1 * step;
    break;
  case 'd':
    vel.x = 1 * step;
    break;
  default:
    break;
  }

  return vel;
}
