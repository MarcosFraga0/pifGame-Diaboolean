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
#include "handlers/keyboardHandler.h"
#include "rooms/dead_room.h"
#include "rooms/first_room.h"
#include "rooms/first_battle_room.h"
#include "rooms/second_room.h"
#include "rooms/desk_corridor.h"
#include "rooms/four_room.h"
#include "rooms/copa_room.h"
#include "rooms/second_battle_room.h"

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
    WHITE
  };

  int playerLife = 3;
  int playerSouls = 1;

  // init config
  screenInit(1);
  keyboardInit();
  timerInit(CLOCK);
  screenUpdate();

  // game rooms
  initFirstRoom(&player, &playerLife, &playerSouls);
  initFirstBattleRoom(&player, &playerLife, &playerSouls);
  initDeadRoom(&player, &playerLife, &playerSouls);
  clearScreen();
  initSecondRoom(&player, &playerLife, &playerSouls);
  initDeadRoom(&player, &playerLife, &playerSouls);
  clearScreen();
  initSecondBattleRoom(&player, &playerLife);

  // stop config
  screenDestroy();
  keyboardDestroy();
  timerDestroy();
  
  return 0;
}