
/**
 * @file types2d.h
 * @date Nov, 10th 2025
 * @brief generic types
 */

#ifndef TYPES2D_H
#define TYPES2D_H

/**
 * @brief Vetor 2D para manipulação no espaço
 */
typedef struct
{
    int x;
    int y;
} Vector2D;

/**
 * @brief Actions that the user can choose
 */
typedef enum
{
    actionNone,
    reset,
    setTrue,
    setFalse,
    negation,
    condition,
    conjunction,
} Action;

/**
 * @brief Collision types for interactions
 */
typedef enum {
    collisionNone,
    damage,
    life,
    trigger,
    bearer,
} CollisionType;

/**
 * @brief Collision struct
 */
typedef struct
{
    int isColliding;
    CollisionType collisionType;
} Collision;

typedef struct {
    int rows;
    int cols;
    Action **grid;
} BattleGrid;

#endif