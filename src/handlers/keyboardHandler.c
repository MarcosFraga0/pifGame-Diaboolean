/**
 * @file keyboardHandler.c
 * @author Juliana
 * @date Nov, 10th 2025
 * @brief generic handlers
 */

#include "handlers/keyboardHandler.h"

/**
 * @brief handler of user actions
 */
Action keyboardActionHandler(char ch){
  Action action = actionNone;
  switch (ch)
  {
  case 'k':
    action = setTrue;
    break;
  case 'l':
    action = setFalse;
    break;
  case 'j':
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
  switch (ch) {
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
