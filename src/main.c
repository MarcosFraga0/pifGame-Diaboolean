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
#include "rooms/first_room.h"
#include "rooms/second_room.h"
#include "rooms/four_room.h"
#include "rooms/copa_room.h"
#include "rooms/second_battle_room.h" // <--- Adicionado o header da sua nova sala

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

  // init config
  screenInit(1);
  keyboardInit();
  timerInit(CLOCK);
  screenUpdate();

  // --- FLUXO DO JOGO ---
  
  // 1. Sala da Copa (Tutorial Movimento)
  //initCopaRoom(&player, &playerLife);
  
  // 2. Limpa tela e inicia Batalha 1 (Tutorial AND com Nariko)
  initSecondBattleRoom(&player, &playerLife); 

  // stop config
  screenDestroy();
  keyboardDestroy();
  timerDestroy();
  
  return 0;
}