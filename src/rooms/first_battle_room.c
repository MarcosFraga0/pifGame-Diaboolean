/**
 * @file first_battle_room.h
 * @date Nov, 24th 2025
 * @brief first battle
 */

#include <stdlib.h>
#include "rooms/first_battle_room.h"

void enemyFisrtLogic(EntityArray* projectsArray, Vector2D* gridVertex, Entity teacherBigLherme);

/**
 * @brief first battle room
 * @param {Entity *player} main player
 * @param {int *playerLife} life player
 */
void initFirstBattleRoom(Entity *player, int *playerLife, int *playerSouls){

    const int enemyTick = 2;
    int countEnemyTick = 0;

    Entity teacherBigLherme = {
        {MAXX / 2 - 2, MAXY / 2 - 5},
        {0, 0},
        {1, 1},
        {0, bearer},
        {"🧑"},
        WHITE,
        WHITE
    };

    /*Starting player in grid*/
    Vector2D initGridPos = {teacherBigLherme.pos.x - 8, teacherBigLherme.pos.y + 3};
    Vector2D initPlayerPos = {initGridPos.x + 2, initGridPos.y + 1};

    // reset entity
    resetEntity(player, initPlayerPos);

    int step = 6;

    /*grid 3x3*/
    int gridLen = 3;
    BattleGrid *battleGrid = createGrid(gridLen, gridLen);
    BattleGrid *battleGridCondition = createGrid(gridLen, gridLen);

    battleGrid->grid[1][1] = negation;
    battleGridCondition->grid[0][1] = setFalse;
    battleGridCondition->grid[2][1] = setTrue;
    battleGridCondition->grid[1][1] = negation;
    battleGridCondition->grid[1][2] = setTrue;
    battleGridCondition->grid[1][0] = setFalse;

    Vector2D gridVertex[4] = {
        /*topLeft*/
        {initGridPos.x - 2, initGridPos.y - 1},
        /*topRight*/
        {initGridPos.x + (step * gridLen), initGridPos.y - 1},
        /*bottomRight*/
        {initGridPos.x + (step * gridLen), initGridPos.y + (step / 2 * gridLen)},
        /*bottomLeft*/
        {initGridPos.x - 2, initGridPos.y + (step / 2 * gridLen)}
    };

    /* nomeBearer */

    /*Define bearer*/
    Entity bearersContent[6] = {
        // top
        {{initGridPos.x, initGridPos.y - 2},
        {0, 0},
        {step * gridLen, 1},
        {0, bearer},
        {"  "},
        WHITE,
        WHITE},
        // right
        {{initGridPos.x + (step * gridLen) + 2, initGridPos.y},
        {0, 0},
        {2, (step / 2) * gridLen},
        {0, bearer},
        {"  "},
        WHITE,
        WHITE},
        // bottom
        {{initGridPos.x, initGridPos.y + 1 + (step / 2) * gridLen},
        {0, 0},
        {step * gridLen, 1},
        {0, bearer},
        {"  "},
        WHITE,
        WHITE},
        // left
        {{initGridPos.x - 4, initGridPos.y},
        {0, 0},
        {2, (step / 2) * gridLen},
        {0, bearer},
        {"  "},
        WHITE,
        WHITE},
        // green conclusion
        {{gridVertex[1].x - 6 * 2, gridVertex[1].y},
        {0, 0},
        {6, 1},
        {0, collisionNone},
        {"-"},
        WHITE,
        RED},
        // red conclusion
        {{gridVertex[1].x, gridVertex[1].y + 4},
        {0, 0},
        {2, 3},
        {0, collisionNone},
        {"⼁"},
        WHITE,
        GREEN}
    };

    EntityArray bearersArray = {
        6,
        bearersContent
    };

    Entity projectsContent[] = {
         /*RIGHT FLAME*/
         {{teacherBigLherme.pos.x + 6, teacherBigLherme.pos.y + 1},
         {0, 0},
         {1, 1},
         {0, damage},
         {"🔥"},
         WHITE,
         WHITE},

         /*TOP FLAME*/
         {{teacherBigLherme.pos.x, teacherBigLherme.pos.y - 2},
         {0, 0},
         {1, 1},
         {0, damage},
         {"🔥"},
         WHITE,
         WHITE},

         /*LEFT FLAME*/
         {{teacherBigLherme.pos.x - 6, teacherBigLherme.pos.y + 1},
         {0, 0},
         {1, 1},
         {0, damage},
         {"🔥"},
         WHITE,
         WHITE}
    };

    EntityArray projectsArray = {
        3,
        projectsContent
    };

    screenClear();
    screenInit(1);
    screenUpdate();

    showBattleRoom(battleGrid, initGridPos);
    showEntities(&projectsArray);
    showEntities(&bearersArray);
    showEntity(&teacherBigLherme);
    showEntity(player);
    showHud(playerLife, playerSouls);
    screenUpdate();
    setSleep(5);

    Action action = actionNone;
    char ch = ' ';

    while (!endBattleCondition(battleGrid, battleGridCondition) && *playerLife > 0)
    {
        if (keyhit()){
            ch = readch();
            setEntityVel(player, keyboardVelHandler(ch, step));
            action = keyboardActionHandler(ch);
            checkCollision(player, &bearersArray);
        }

        if (timerTimeOver()){
            showHud(playerLife, playerSouls);
            showBattleRoom(battleGrid, initGridPos);

            Vector2D playerGridPos = getGridPos(player, gridVertex, initPlayerPos, step);
            actionRoom(action, battleGrid, playerGridPos);
            for(int i = 0; i < 3; i++){
                Vector2D projectGridPos = getGridPos(&projectsContent[i], gridVertex, initPlayerPos, step);
                actionRoom(reset, battleGrid, projectGridPos);
            }

            showEntities(&bearersArray);
            showEntityNoMove(&teacherBigLherme);
            showEntity(player);
            for(int i = 0; i < 3; i++){
                Entity *project = &projectsArray.entities[i];
                showEntityNoMove(project);
            }
            
            enemyFisrtLogic(&projectsArray, gridVertex, teacherBigLherme);

            // check collision between player and enemy/project
            checkCollision(player, &projectsArray);

            screenUpdate();
            countEnemyTick++;
        }

        if(countEnemyTick == enemyTick){
            for(int i = 0; i < 3; i++){
                Entity *project = &projectsArray.entities[i];
                showEntityNoStop(project);
                screenUpdate();
            }

            if(player->collision.collisionType == damage){
                *playerLife -= 1;
                player->collision.collisionType = collisionNone;
            }

            countEnemyTick = 0;
        }
    }

    showDialogBox("🧑", "Big Lherme", "voce nao sabe Logica!");
    showDialogBox("🧑", "Big Lherme", "como castigo, levarei sua ALMA!!");
    playerLoseSoul(player);
    *playerSouls = 0;
    
    showHud(playerLife, playerSouls);

    destroyGrid(battleGrid);
    destroyGrid(battleGridCondition);
}

void enemyFisrtLogic(EntityArray* projectsArray, Vector2D* gridVertex, Entity teacherBigLherme){
    Vector2D initialProjectsPos[] = {
        /*RIGHT FLAME*/
        {teacherBigLherme.pos.x + 6, teacherBigLherme.pos.y + 1},
        /*TOP FLAME*/
        {teacherBigLherme.pos.x, teacherBigLherme.pos.y - 2},
        /*LEFT FLAME*/
        {teacherBigLherme.pos.x - 6, teacherBigLherme.pos.y + 1}
    };

    int isProjectsStop = 1;

    for(int i = 0; i < 3; i++){
        Entity *project = &projectsArray->entities[i];

        if(project->pos.y > gridVertex[2].y){
            project->vel.y = 0;
            project->pos.y = initialProjectsPos[i].y;
        }

        if(project->vel.y != 0){
            isProjectsStop = 0;
        }
    }

    if(!isProjectsStop){
        return;
    }

    int random = (rand() % (2 - 0 + 1));

    Entity *project = &projectsArray->entities[random];
    project->vel.y = 3;
}