/**
 * @file screenHandler.h
 * @date Nov, 13th 2025
 * @brief generic handlers screen
 */

#ifndef SCREEN_HANDLER_H
#define SCREEN_HANDLER_H

#include "screen.h"
#include "timer.h"

void printText(char *text, int x, int y, screenColor fg, screenColor bg);

void clearScreen();

#endif