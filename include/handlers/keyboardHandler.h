/**
 * @file keyboardHandler.h
 * @date Nov, 10th 2025
 * @brief generic handlers
 */

#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H
#include "types/types2d.h"

Action keyboardActionHandler(char ch);

Vector2D keyboardVelHandler(char ch, int step);

#endif