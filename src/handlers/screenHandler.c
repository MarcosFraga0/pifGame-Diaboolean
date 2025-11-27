/**
 * @file screenHandler.c
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

/**
 * @brief limpa a tela com uma animação
 */
void clearScreen()
{
  int i = 0;
  while (i <= MAXY + 2)
  {
    if (timerTimeOver() == 1)
    {
      for (int y = 0; y < i; y++){
        for (int x = 0; x < MAXX; x++)
        {
          screenGotoxy(x, y);
          printf(" ");
        }
      }
      screenUpdate();
      i+=2;
    }
  }
}