/**
 * @file second_room.h
 * @author Marcos
 * @date Nov, 10th 2025
 * @details second game room
 */

#ifndef SECOND_ROOM_H
#define SECOND_ROOM_H
 
#include "animations/player.h"
#include "rooms/battle_room.h"
#include "handlers/timeHandler.h"
#include "handlers/screenHandler.h"
#include "ui/dialog_box.h"
#include "ui/menu.h"
#include "ui/hud.h"

void initSecondRoom(Entity *player, int *playerLife, int *playerSouls);

#endif