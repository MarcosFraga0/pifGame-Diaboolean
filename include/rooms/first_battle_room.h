/**
 * @file first_battle_room.h
 * @date Nov, 24th 2025
 * @brief first battle
 */

#ifndef FIRST_BATTLE_ROOM_H
#define FIRST_BATTLE_ROOM_H

#include "screen.h"
#include "timer.h"
#include "keyboard.h"

#include "handlers/keyboardHandler.h"
#include "handlers/timeHandler.h"
#include "entities/entity.h"
#include "ui/dialog_box.h"
#include "ui/menu.h"
#include "ui/hud.h"
#include "rooms/battle_room.h"

void initFirstBattleRoom(Entity *player, int *playerLife, int *playerSouls);

#endif