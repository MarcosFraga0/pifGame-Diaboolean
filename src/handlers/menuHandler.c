/**
 * @file menuHandler.c
 * @author Vinicius Braz (gitviiini)
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
    // do nothing
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