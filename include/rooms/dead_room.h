/**
 * @file dead_room.h
 * @author Vinicius Braz (gitviini)
 * @date Nov, 25th 2025
 * @brief dead's room
 */

#ifndef DEAD_ROOM_H
#define DEAD_ROOM_H

#include "screen.h"
#include "timer.h"
#include "keyboard.h"

#include "handlers/keyboardHandler.h"
#include "handlers/timeHandler.h"
#include "entities/entity.h"
#include "ui/dialog_box.h"
#include "ui/menu.h"
#include "ui/hud.h"
#include "animations/player.h"

void initDeadRoom(Entity *player, int *playerLife, int *playerSouls);

#endif