/**
 * @file battle_room.c
 * @author Vinicius Braz (gitviini)
 * @date Nov, 9th 2025
 * @details Battle room example
 */

#ifndef BATTLE_ROOM_H
#define BATTLE_ROOM_H

#include "screen.h"
#include "timer.h"
#include "keyboard.h"

#include "types/types2d.h"
#include "handlers/keyboardHandler.h"
#include "handlers/actionRoomHandler.h"
#include "entities/entity.h"

// simbolos lógicos
extern char NEGATION[];
extern char CONDITION[];

BattleGrid *createGrid(int rows, int cols);

void destroyGrid(BattleGrid *battleGrid);

Vector2D getGridPos(Entity *entity, Vector2D *gridVertex, Vector2D initial, int step);

void actionRoom(Action action, BattleGrid *battleGrid, Vector2D playerGridPos);

void showBattleRoom(BattleGrid *battleGrid, Vector2D initialGridPos);

int endBattleCondition(BattleGrid *battleGrid, BattleGrid *battleGridCondition);

#endif