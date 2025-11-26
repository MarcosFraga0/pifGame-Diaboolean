/**
 * @file actionRoomHandler.c
 * @author Vinicius Braz (gitviini)
 * @date Nov, 13th 2025
 * @brief handler of action room
 */

#include "handlers/actionRoomHandler.h"
#include <stdio.h>

/**
 * @brief Applies propositional logic for conditional (P -> Q)
 * @param {Action premise} The antecedent
 * @param {Action conclusion} The consequent
 * @return {Action} The result (setTrue or setFalse), or actionNone if inputs are invalid
 */
Action conditionLogic(Action premise, Action conclusion)
{
    // único resultado falso (true -> false) = false
    if (premise == setTrue && conclusion == setFalse)
    {
        return setFalse;
    }

    // verifica se premise e conclusion são valores lógicos
    if ((premise == setTrue || premise == setFalse) && (conclusion == setTrue || conclusion == setFalse))
    {
        return setTrue;
    }

    // se não forem valores válidos, retorna nada
    return actionNone;
}

/**
 * @brief handler condition symbol effects
 * @param {Vector2D conditionPos} condition position in grid
 * @param {Vector2D playerGridPos} player position in grid
 * @param {BattleGrid *battleGrid} battle grid pointer
 */
void conditionHandler(Vector2D conditionPos, Vector2D playerGridPos, BattleGrid *battleGrid){
    int y = conditionPos.y;
    int x = conditionPos.x;

    // verificação vertical (top -> bottom) = right
    // verifica se há espaço para os valores e se player is around
    if((playerGridPos.y == y - 1 || playerGridPos.y == y + 1) && y > 0 && y < battleGrid->rows - 1 && x < battleGrid->cols - 1){
        Action top = battleGrid->grid[y - 1][x];
        Action bottom = battleGrid->grid[y + 1][x];

        Action result = conditionLogic(top, bottom);

        battleGrid->grid[y][x + 1] = result;
    }

    // verificação horizontal (left -> right) = bottom e se player is around
    if((playerGridPos.x == x - 1 || playerGridPos.x == x + 1) && x > 0 && x < battleGrid->cols - 1 && y < battleGrid->rows - 1){
        Action left = battleGrid->grid[y][x - 1];
        Action right = battleGrid->grid[y][x + 1];

        Action result = conditionLogic(left, right);

        battleGrid->grid[y + 1][x] = result;
    }
}

/**
 * @brief apply negation logic
 * @param {Action action} target action
 * @return {Action} Opposite action
 */
Action negationLogic(Action action)
{
    Action _action = actionNone;

    switch (action)
    {
    case setTrue:
        _action = setFalse;
        break;
    case setFalse:
        _action = setTrue;
        break;
    default:
        break;
    }

    return _action;
}

/**
 * @brief applyer symbol negation effects
 * @param {Action actionPlayer} player action
 * @param {Vector2D negationPos} negation position in grid
 * @param {Vector2D playerGridPos} player position in grid pos
 * @param {BattleGrid *battleGrid} battle grid pointer
 */
void negationHandler(Action actionPlayer, Vector2D negationPos, Vector2D playerGridPos, BattleGrid *battleGrid)
{
    int y = negationPos.y;
    int x = negationPos.x;

    Action *actionTop = &battleGrid->grid[y - 1][x];
    Action *actionBottom = &battleGrid->grid[y + 1][x];
    Action *actionLeft = &battleGrid->grid[y][x - 1];
    Action *actionRight = &battleGrid->grid[y][x + 1];

    // if top set in bottom
    if (y - 1 == playerGridPos.y && x == playerGridPos.x)
    {
        *actionBottom = negationLogic(actionPlayer);
    }
    // if bottom set in top
    else if (y + 1 == playerGridPos.y && x == playerGridPos.x)
    {
        *actionTop = negationLogic(actionPlayer);
    }
    // if left set in right
    else if (x - 1 == playerGridPos.x && y == playerGridPos.y)
    {
        *actionRight = negationLogic(actionPlayer);
    }
    // if right set in left
    else if (x + 1 == playerGridPos.x && y == playerGridPos.y)
    {
        *actionLeft = negationLogic(actionPlayer);
    }
}

/**
 * @brief apply conjunction logic (AND)
 * @param {Action p} first value
 * @param {Action q} second value
 * @return {Action} Result action (setTrue or setFalse)
 */

Action conjunctionLogic(Action p, Action q)
{
    // Se qualquer um for Falso, o resultado é Falso
    if (p == setFalse || q == setFalse) return setFalse;
    // Se ambos forem Verdadeiros, o resultado é Verdadeiro
    if (p == setTrue && q == setTrue) return setTrue;
    return actionNone;
}

/**
 * @brief applyer symbol conjunction effects
 * @param {Vector2D conjunctionPos} conjunction position in grid
 * @param {Vector2D playerGridPos} player position in grid pos
 * @param {BattleGrid *battleGrid} battle grid pointer
 */

void conjunctionHandler(Vector2D pos, Vector2D playerGridPos, BattleGrid *battleGrid){
    int y = pos.y;
    int x = pos.x;

    // Vertical (Cima e Baixo -> Resultado na Direita) 
    if((playerGridPos.y == y - 1 || playerGridPos.y == y + 1) && y > 0 && y < battleGrid->rows - 1 && x < battleGrid->cols - 1){
        Action top = battleGrid->grid[y - 1][x];
        Action bottom = battleGrid->grid[y + 1][x];
        battleGrid->grid[y][x + 1] = conjunctionLogic(top, bottom);
    }

    // Horizontal (Esq e Dir -> Resultado em Baixo)
    if((playerGridPos.x == x - 1 || playerGridPos.x == x + 1) && x > 0 && x < battleGrid->cols - 1 && y < battleGrid->rows - 1){
        Action left = battleGrid->grid[y][x - 1];
        Action right = battleGrid->grid[y][x + 1];
        battleGrid->grid[y + 1][x] = conjunctionLogic(left, right);
    }
}

/**
 * @brief handler actions of room
 * @param {Action actionPlayer} player action
 * @param {Vector2D playerGridPos} player position in grid pos
 * @param {BattleGrid *battleGrid} battle grid pointer
 */
void actionRoomHandler(Action actionPlayer, Vector2D playerGridPos, BattleGrid *battleGrid)
{
    for (int y = 0; y < battleGrid->rows; y++)
    {
        for (int x = 0; x < battleGrid->cols; x++)
        {
            Vector2D actionPos = {x, y};
            Action action = battleGrid->grid[y][x];

            switch (action)
            {
            case negation:
                negationHandler(actionPlayer, actionPos, playerGridPos, battleGrid);
                break;
            case condition:
                conditionHandler(actionPos, playerGridPos, battleGrid);
                break;
            case conjunction:
                conjunctionHandler(actionPos, playerGridPos, battleGrid);
                break;
            default:
                break;
            }
        }
    }
}