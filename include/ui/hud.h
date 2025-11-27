/**
 * @file hud.h
 * @date Nov, 24th 2025
 * @brief show hud in display
 */

#ifndef HUD_H
#define HUD_H

#include "screen.h"
#include "keyboard.h"

#include "entities/entity.h"
#include "handlers/timeHandler.h"
#include "handlers/screenHandler.h"
#include "types/types2d.h"
#include "handlers/menuHandler.h"

void showHud(int *playerLife, int *playerSouls);

#endif