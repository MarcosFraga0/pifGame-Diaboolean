/**
 * @file four_room.h
 * @author Vinicius Braz (gitviini)
 * @date Nov, 19th 2025
 */

#ifndef FOUR_ROOM_H
#define FOUR_ROOM_H

#include "screen.h"
#include "timer.h"
#include "keyboard.h"

#include "animations/player.h"
#include "handlers/keyboardHandler.h"
#include "handlers/timeHandler.h"
#include "entities/entity.h"

void initFourRoom(Entity *player, int *playerLife);

#endif