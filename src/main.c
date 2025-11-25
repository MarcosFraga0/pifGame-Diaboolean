/**
 * @file main.c
 * @author Vinicius Braz (gitviini)
 * @date Nov, 9th 2025
 * @details Roda lógica principal do game
 */

#include <stdio.h>
#include <locale.h> // <--- 1. Adicionei para corrigir os emojis no meu PC

#include "keyboard.h"
#include "screen.h"
#include "timer.h"

#include "entities/entity.h"
#include "handlers/keyboardHandler.h"
#include "rooms/first_room.h"
#include "rooms/second_room.h"
#include "rooms/four_room.h"
#include "rooms/copa_room.h"
#include "rooms/second_battle_room.h"

#define CLOCK 100

int main()
{
  // 2. Configura o locale para aceitar caracteres especiais/emojis
  setlocale(LC_ALL, ""); 

  // main entity
  Entity player = {
    {4, 8},
    {0, 0},
    {2, 1}, // <--- 3. ALTERADO DE {1, 1} PARA {2, 1} (Largura 2 para cobrir o emoji e não deixar rastro)
    {0, collisionNone},
    {"🤓"},
    WHITE,
    WHITE
  };

  int playerLife = 3;

  // init config
  screenInit(1);
  keyboardInit();
  timerInit(CLOCK);
  screenUpdate();

  // game rooms
  // initFirstRoom(&player, &playerLife); 
  // clearScreen();
  
  initCopaRoom(&player, &playerLife);

  clearScreen();
  initSecondBattleRoom(&player, &playerLife);
  
  /* initSecondRoom(&player, &playerLife);
  clearScreen();
  initFourRoom(&player, &playerLife);
  clearScreen(); 
  */

  // stop config
  screenDestroy();
  keyboardDestroy();
  timerDestroy();
  
  return 0;
}