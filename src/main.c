/**
 * @file main.c
 * @author Vinicius Braz (gitviini)
 * @date Nov, 9th 2025
 * @details Roda lógica principal do game
 */

#include <stdio.h>

#include "keyboard.h"
#include "screen.h"
#include "timer.h"

#include "entities/entity.h"
#include "handlers/keyboardHandler.h"
#include "rooms/first_room.h"
#include "rooms/second_room.h"

#define CLOCK 100

void clearScreen();

int main()
{
  // main entity
  Entity player = {
    {4, 8},
    {0, 0},
    {1, 1},
    {0, collisionNone},
    {"🤓"},
    WHITE,
    WHITE
  };

  // init config
  screenInit(1);
  keyboardInit();
  timerInit(CLOCK);
  screenUpdate();

  // game rooms
  initFirstRoom(&player);
  clearScreen();
  initSecondRoom(&player);
  clearScreen();

  // stop config
  screenDestroy();
  keyboardDestroy();
  timerDestroy();
  return 0;
}

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