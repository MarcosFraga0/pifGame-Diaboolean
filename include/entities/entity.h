/**
 * @file entity.h
 * @date Nov, 9th 2025
 * @details Implement entity features
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "screen.h"


#include "types/types2d.h"

/**
 * @brief Entidade genérica
 * @attention {char sprite[40]} unicodes podem ocupar mais de 5 chars, aumentar espaço caso necessário
 */
typedef struct {
  Vector2D pos;
  Vector2D vel;
  Vector2D len;
  Collision collision;
  char sprite[15][41];
  screenColor fg;
  screenColor bg;
} Entity;

/**
 * @brief Colection de Entidades genéricas
 */
typedef struct {
  int len;
  Entity *entities;
} EntityArray;

void resetEntity(Entity *entity, Vector2D initial);

void setEntityVel(Entity *entity, Vector2D vel);

void entityMove(Entity *entity);

void showEntity(Entity *entity);

void showEntityNoMove(Entity *entity);

void showEntityNoStop(Entity *entity);

void showEntities(EntityArray *entities);

void checkCollision(Entity *entity, EntityArray *entities);

#endif