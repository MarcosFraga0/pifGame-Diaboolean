/**
 * @file first_room.h
 * @author Joanna
 * @date Nov, 25th 2025
 * @details Desk corridor (restore life and catch souls)
 */

 #ifndef DESK_CORRIDOR_H
 #define DESK_CORRIDOR_H

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

void initDeskCorridor(Entity *player, int *playerLife, int *playerSouls);

#endif