/**
 * @file player.h
 * @author Vinicius Braz (gitviini)
 * @date Nov, 22th 2025
 * @brief player animations
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "screen.h"

#include "entities/entity.h"
#include "handlers/screenHandler.h"
#include "handlers/timeHandler.h"

void playerLoseLife(Entity *player);

void playerAddLife(Entity *player);

#endif