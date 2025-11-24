/**
 * @file first_room.h
 * @author Matheus de freitas
 * @date Nov, 10th 2025
 * @details first game room
 */

#ifndef FIRST_ROOM_H
#define FIRST_ROOM_H
 
#include "screen.h"
#include "timer.h"
#include "keyboard.h"

#include "handlers/keyboardHandler.h"
#include "handlers/timeHandler.h"
#include "entities/entity.h"
#include "ui/dialog_box.h"
#include "ui/menu.h"
#include "rooms/battle_room.h"

void initFirstRoom(Entity *player, int *playerLife);

#endif