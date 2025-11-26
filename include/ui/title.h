/**
 * @file title.h
 * @author Vinicius Braz (gitviini)
 * @date Nov, 26th 2025
 * @brief draw title in screen
 */

#ifndef TITLE_H
#define TITLE_H

#include "screen.h"
#include "timer.h"
#include "keyboard.h"

#include "types/types2d.h"
#include "handlers/screenHandler.h"

void showText(char *text, Vector2D initTitlePos);

#endif