/**
 * @file battle_room.c
 * @date Nov, 9th 2025
 * @details Battle room example
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rooms/battle_room.h"

// simbolos lógicos
char NEGATION[] = "-¬";
char CONDITION[] = "->";
char CONJUNCTION[] = "^";

/**
 * @brief create new battle grid
 * @param {int rows} number of rows
 * @param {int cols} number of columns
 * @returns {BattleGrid*} if allocation sucess
 * @returns {NULL} if allocation fails
 */
BattleGrid *createGrid(int rows, int cols){
    Action **grid;
    grid = (Action**) malloc(sizeof(Action*) * rows);

    // if grid isn't allocated, free grid and returns null
    if(!grid){
        free(grid);
        return NULL;
    }
    
    for(int i = 0; i < rows; i++){
        grid[i] = (Action*) malloc(sizeof(Action) * cols);

        // if grid isn't allocated, free all and returns null
        if(!grid[i]){
            for(int a = 0; a < i; a++) free(grid[a]);
            free(grid);
            return NULL;
        }
    }

    BattleGrid *battleGrid = malloc(sizeof(BattleGrid));

    // if it isn't allocated, free all and returns null
    if(!battleGrid){
        for(int a = 0; a < rows; a++) free(grid[a]);
        free(grid);
        free(battleGrid);
        return NULL;
    }

    // fill grid
    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            grid[y][x] = actionNone;
        }
    }

    // if it is allocated, set attributes
    battleGrid->rows = rows;
    battleGrid->cols = cols;
    battleGrid->grid = grid;

    return battleGrid;
}

/**
 * @brief free battleGrid memory allocated
 * @param {BattleGrid *battleGrid} pre-allocated grid
 */
void destroyGrid(BattleGrid *battleGrid){
    // if battleGrid isn't allocated, return
    if(!battleGrid){
        return;
    }

    // if battleGrid is allocated, free all
    for(int i = 0; i < battleGrid->rows; i++) free(battleGrid->grid[i]);
    free(battleGrid->grid);
    free(battleGrid);
}

/**
 * @brief get entity position in grid
 * @param {Entity *entity} entity pointer
 * @param {Vector2D *gridVertex} array de vertices da grid
 * @param {Vector2D initial} initial coordinates of entity in room
 * @param {int step} entity space between steps
 */
Vector2D getGridPos(Entity *entity, Vector2D *gridVertex, Vector2D initial, int step){
    Vector2D grid = {-1,-1};

    if(entity->pos.x >= gridVertex[0].x && entity->pos.x <= gridVertex[2].x && entity->pos.y >= gridVertex[0].y && entity->pos.y <= gridVertex[2].y){
        grid.x = (entity->pos.x - initial.x) / step;
        grid.y = (entity->pos.y - initial.y) / (step / 2);
    }
    return grid;
}

/**
 * @brief show the effects of user actions on room map
 * @param {Action action} trigger action
 * @param {BattleGrid *battleGrid} battleGrid
 * @param {Vector2D ActionGridPos} action position 
 */
void actionRoom(Action action, BattleGrid *battleGrid, Vector2D ActionGridPos)
{
    // ação acontece fora da grid
    if(ActionGridPos.x < 0 || ActionGridPos.y < 0){
        return;
    }

    Action actionPrevious = battleGrid->grid[ActionGridPos.y][ActionGridPos.x];

    if (!action)
    {
        return;
    }

    if(actionPrevious == setTrue || actionPrevious == setFalse || actionPrevious == reset || actionPrevious == actionNone){
        // set new action in battlegrid (y, x)
        battleGrid->grid[ActionGridPos.y][ActionGridPos.x] = action;
    }

    actionRoomHandler(action, ActionGridPos, battleGrid);
}

/**
 * @brief draw squares in battleGrid
 * @param {Action action} action that in the square
 * @param {Vector2D pos} initial square position
 * @param {int len} space between the squares centers
 * @param {screenColor fg} foreground color
 * @param {screenColor bg} background color
 */
void drawSquare(Action action, Vector2D initPos, char *text, int len, screenColor fg, screenColor bg){
    Vector2D topLeft = {initPos.x, initPos.y};
    Vector2D topRight = {initPos.x + len, initPos.y};
    Vector2D bottomRight = {initPos.x + len, initPos.y + (len / 2)};
    Vector2D bottomLeft = {initPos.x, initPos.y + (len / 2)};

    /**
     * @brief draw 2x1
     * @attention desenhar 2 horizontais para 1 vertical ajuda a manter a proporção em tela
     */
    for(int y = 0; y < len / 2; y++){
        for(int x = 0; x < len; x+=2){
            screenGotoxy(topLeft.x + x, topLeft.y + y);

            // fill center square with text
            if(x == 2 && y == 1){
                screenSetNormal();
                printf("%s", text);
                continue;
            }

            // draw square borders
            screenSetColor(fg, bg);
            printf("  ");
            screenSetNormal();
        }
    }

    screenUpdate();
}

/**
 * @brief draw grid
 * @param {BattleGrid *battleGrid} battleGrid that will be shown
 * @param {Vector2D initialGridPos} where grid is drawing
 */
void showBattleRoom(BattleGrid *battleGrid, Vector2D initialGridPos)
{
    const int lenx = 6;
    const int leny = lenx / 2;

    // iteration indexs (y, x)
    for (int i_y = 0; i_y < battleGrid->rows; i_y++)
    {
        for (int i_x = 0; i_x < battleGrid->cols; i_x++)
        {
            Vector2D initSquarePos = {(i_x * lenx) + initialGridPos.x, (i_y * leny) + initialGridPos.y};

            // get action specific
            Action action = battleGrid->grid[i_y][i_x];

            // initial text is blank
            char text[10] = "  ";
            
            // choose colors by action
            screenColor fg = WHITE, bg = WHITE;
            switch (action)
            {
            case setTrue:
                bg = GREEN;
                break;
            case setFalse:
                bg = RED;
                break;
            case actionNone:
            case reset:
                bg = MAGENTA;
                break;
            default:
                bg = MAGENTA;
                break;
            }

            // choose text that will be printed inside square
            switch (action)
            {
            case negation:
                strcpy(text, NEGATION);
                break;
            case condition:
                strcpy(text, CONDITION);
                break;
            case conjunction:
                strcpy(text, CONJUNCTION);
                break;
            default:
                break;
            }

            drawSquare(action, initSquarePos, text, lenx, fg, bg);
        }
    }
}

/**
 * @brief verify if end battle condition is true
 * @param {BattleGrid *battleGrid} grid of battle
 * @param {BattleGrid *battleGridCondition} grid with conditions
 * @returns {1} if end battle
 * @returns {0} if continue
 */
int endBattleCondition(BattleGrid *battleGrid, BattleGrid *battleGridCondition)
{
    // verdadeiro por default
    int result = 1;
    for (int y = 0; y < battleGrid->rows; y++)
    {
        for (int x = 0; x < battleGrid->cols; x++)
        {
            /**
             * @details caso haja uma condição (true|false), mas não for atendida, atribui falso
             */
            if (
                battleGridCondition->grid[y][x] != actionNone &&
                battleGridCondition->grid[y][x] != battleGrid->grid[y][x])
            {
                result = 0;
            }
        }
    }

    return result;
}