/**
 * @file hud.c
 * @author Vinicius Braz (gitviini)
 * @date Nov, 24th 2025
 * @brief show hud in display
 */

#include <stdio.h>
#include "ui/hud.h"

/**
 * @brief show player's hearts at top left window
 */
void showPlayerHeart(int playerLife){
    int maxPlayerLife = 4;
    // TOP LEFT
    Vector2D initHeartHudPos = {MINX + 2, MINY + 1};

    screenGotoxy(initHeartHudPos.x, initHeartHudPos.y);
    // clear
    for(int x = 0; x < maxPlayerLife; x++){
        printf("   ");
    }

    screenGotoxy(initHeartHudPos.x, initHeartHudPos.y);
    // draw
    screenSetColor(RED, WHITE);
    for(int x = 0; x < playerLife; x++){
        printf("♥️ ");
    }
    screenSetNormal();
}

void showSouls(int playerSouls){
    int maxHeart = 4;
    // TOP RIGHT
    Vector2D initSoulsHudPos = {MAXX - 6 - MINX, MINY + 1};

    char numberSouls[3];

    sprintf(numberSouls, "%d", playerSouls);

    screenGotoxy(initSoulsHudPos.x, initSoulsHudPos.y);
    // clear
    printText("     ", initSoulsHudPos.x, initSoulsHudPos.y, WHITE, WHITE);

    screenGotoxy(initSoulsHudPos.x, initSoulsHudPos.y);
    // draw
    printf("👻 %s", numberSouls);
}

/**
 * @brief show hud in display
 */
void showHud(int *playerLife, int *playerSouls){
    showPlayerHeart(*playerLife);
    showSouls(*playerSouls);
}