/**
 * @file four_battle_room.h
 * @date Nov, 27th 2025
 * @brief four battle room logic
 */

#ifndef FOUR_BATTLE_ROOM_H
#define FOUR_BATTLE_ROOM_H

#include "screen.h"
#include "timer.h"
#include "keyboard.h"

#include "animations/player.h"
#include "handlers/keyboardHandler.h"
#include "handlers/timeHandler.h"
#include "entities/entity.h"
#include "ui/dialog_box.h"
#include "ui/menu.h"
#include "ui/hud.h"
#include "rooms/battle_room.h"

void initFourOneBattleRoom(Entity *player, int *playerLife, int *playerSouls);
void initFourTwoBattleRoom(Entity *player, int *playerLife, int *playerSouls);

#endif