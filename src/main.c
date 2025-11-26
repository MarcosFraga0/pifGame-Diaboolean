/**
 * @file main.c
 * @author Vinicius Braz (gitviini)
 * @date Nov, 9th 2025
 * @details Roda lógica principal do game
 */

#include <stdio.h>
#include <locale.h>

#include "keyboard.h"
#include "screen.h"
#include "timer.h"

#include "entities/entity.h"
#include "handlers/fileHandler.h"
#include "handlers/keyboardHandler.h"
#include "rooms/dead_room.h"
#include "rooms/first_room.h"
#include "rooms/first_battle_room.h"
#include "rooms/second_battle_room.h"
#include "rooms/second_room.h"
#include "rooms/third_room.h"
#include "rooms/third_battle_room.h"
#include "rooms/four_room.h"

#define CLOCK 100

int main()
{
  // Configura o locale para aceitar caracteres especiais/emojis
  setlocale(LC_ALL, "");

  // main entity
  Entity player = {
      {4, 8},
      {0, 0},
      {2, 1},
      {0, collisionNone},
      {"🤓"},
      WHITE,
      WHITE};

  int playerLife = 3;
  int playerSouls = 1;
  int playerRoom = 1;

  getInfoInFile(&playerLife, &playerSouls, &playerRoom);

  // init config
  screenInit(1);
  keyboardInit();
  timerInit(CLOCK);
  screenUpdate();

  if (playerRoom == 1)
  {
    screenClear();
    screenInit(1);
    // game rooms
    initFirstRoom(&player, &playerLife, &playerSouls);
    initFirstBattleRoom(&player, &playerLife, &playerSouls);
    playerRoom++;
    setInfoInFile(&playerLife, &playerSouls, &playerRoom);
  }
  if (playerRoom == 2)
  {
    if (playerLife == 0)
    {
      initDeadRoom(&player, &playerLife, &playerSouls);
    }
    screenClear();
    screenInit(1);
    initSecondRoom(&player, &playerLife);
    initSecondBattleRoom(&player, &playerLife, &playerSouls);
    playerRoom++;
    setInfoInFile(&playerLife, &playerSouls, &playerRoom);
  }
  if (playerRoom == 3)
  {
    if (playerLife == 0)
    {
      initDeadRoom(&player, &playerLife, &playerSouls);
    }
    screenClear();
    screenInit(1);
    initThirdRoom(&player, &playerLife, &playerSouls);
    initThridBattleRoom(&player, &playerLife, &playerSouls);
  }
  if (playerRoom == 4)
  {
    screenClear();
    screenInit(1);
    initFourRoom(&player, &playerLife, &playerSouls);
    if (playerLife == 0)
    {
      initDeadRoom(&player, &playerLife, &playerSouls);
    }
  }

  // stop config
  screenDestroy();
  keyboardDestroy();
  timerDestroy();

  return 0;
}