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
#include "rooms/four_room.h"

#define CLOCK 100

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
  /* initFirstRoom(&player);
  clearScreen();
  initSecondRoom(&player);
  clearScreen(); */
  initFourRoom(&player);

  // stop config
  screenDestroy();
  keyboardDestroy();
  timerDestroy();
  
  return 0;
}