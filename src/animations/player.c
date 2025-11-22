/**
 * @file player.c
 * @author Vinicius Braz (gitviini)
 * @date Nov, 22th 2025
 * @brief player animations
 */

#include <stdio.h>

#include "animations/player.h"

void playerLoseLife(Entity *player)
{
    // player lose animation
    printText("♥️", player->pos.x, player->pos.y, WHITE, WHITE);
    setSleep(5);
    printText(" ", player->pos.x, player->pos.y, WHITE, WHITE);
    printText("♥️", player->pos.x, player->pos.y - 1, WHITE, WHITE);
    setSleep(10);
    printText("💔", player->pos.x, player->pos.y - 1, WHITE, WHITE);
    screenUpdate();
    setSleep(15);
    /* setSleep(15);
    screenClear();
    screenInit(1);
    printText("VOCÊ PERDEU!", MAXX / 2 - 6, MAXY / 2, RED, WHITE);
    screenUpdate(); */
}

void playerAddLife(Entity *player)
{
    // under player
    int x = player->pos.x;
    int y = player->pos.y - 1;

    printText("+♥️", x, y, WHITE, WHITE);
    screenUpdate();
    setSleep(5);
    printText("   ", x, y, WHITE, WHITE);
    screenUpdate();
}