/**
 * @file screenHandler.c
 * @author Joanna
 * @date Nov, 13th 2025
 * @brief generic handlers screen
 */

#include <stdio.h>

#include "handlers/screenHandler.h"

/**
 * @brief print texts in especific position
 * @param {char *text} text that will be printed
 * @param {int x} x axes position
 * @param {int y} y axes position
 * @param {screenColor fg} foreground color
 * @param {screenColor bg} background color
 */
void printText(char *text, int x, int y, screenColor fg, screenColor bg)
{
    screenGotoxy(x, y);
    screenSetColor(fg, bg);
    printf("%s", text);
    screenSetNormal();
    screenUpdate();
}