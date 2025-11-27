/**
 * @file menuHandler.c
 * @date Nov, 23th 2025
 * @details manipuladores do menu
 */

#include <stdlib.h>

#include "handlers/menuHandler.h"

/**
 * @brief continue game
 */
void continueOption()
{
    clearScreen();
    screenInit(1);
}

/**
 * @brief exit game
 */
void exitGameOption()
{
    screenDestroy();
    keyboardDestroy();
    timerDestroy();
    exit(0);
}