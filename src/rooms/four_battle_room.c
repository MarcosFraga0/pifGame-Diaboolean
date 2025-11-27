/**
 * @file four_battle_room.h
 * @date Nov, 27th 2025
 * @brief four battle room logic
 */

#include <string.h>
#include <stdlib.h>
#include "rooms/four_battle_room.h"

void enemyFourOneLogic(EntityArray *projectsArray, Vector2D *gridVertex, Entity teacherBigLherme);

/**
 * @brief four one battle room
 * @param {Entity *player} main player
 * @param {int *playerLife} life player
 * @param {int *playerSouls} souls player
 */
void initFourOneBattleRoom(Entity *player, int *playerLife, int *playerSouls)
{

    const int enemyTick = 2;
    int countEnemyTick = 0;

    Entity teacherBigLherme = {
        {MAXX / 2 - 2, MAXY / 2 - 5},
        {0, 0},
        {1, 1},
        {0, bearer},
        {"🧑"},
        WHITE,
        WHITE};

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
        {initGridPos.x - 2, initGridPos.y + (step / 2 * gridLen)}};

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
         GREEN}};

    EntityArray bearersArray = {
        6,
        bearersContent};

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
         WHITE}};

    EntityArray projectsArray = {
        3,
        projectsContent};

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

    showDialogBox(teacherBigLherme.sprite[0], "Big Lherme", "entao voce voltou novamente?");
    showDialogBox(player->sprite[0], "Nerd", "eu vou lhe derrotar!");
    setSleep(5);

    Action action = actionNone;
    char ch = ' ';

    while (!endBattleCondition(battleGrid, battleGridCondition) && *playerLife > 0)
    {
        if (keyhit())
        {
            ch = readch();
            setEntityVel(player, keyboardVelHandler(ch, step));
            action = keyboardActionHandler(ch);
            checkCollision(player, &bearersArray);
        }

        if (timerTimeOver())
        {
            showHud(playerLife, playerSouls);
            showBattleRoom(battleGrid, initGridPos);

            Vector2D playerGridPos = getGridPos(player, gridVertex, initPlayerPos, step);
            actionRoom(action, battleGrid, playerGridPos);
            for (int i = 0; i < 3; i++)
            {
                Vector2D projectGridPos = getGridPos(&projectsContent[i], gridVertex, initPlayerPos, step);
                actionRoom(reset, battleGrid, projectGridPos);
            }

            showEntities(&bearersArray);
            showEntityNoMove(&teacherBigLherme);
            showEntity(player);
            for (int i = 0; i < 3; i++)
            {
                Entity *project = &projectsArray.entities[i];
                showEntityNoMove(project);
            }

            enemyFourOneLogic(&projectsArray, gridVertex, teacherBigLherme);

            // check collision between player and enemy/project
            checkCollision(player, &projectsArray);

            screenUpdate();
            countEnemyTick++;
        }

        if (countEnemyTick == enemyTick)
        {
            for (int i = 0; i < 3; i++)
            {
                Entity *project = &projectsArray.entities[i];
                showEntityNoStop(project);
                screenUpdate();
            }

            if (player->collision.collisionType == damage)
            {
                *playerLife -= 1;
                player->collision.collisionType = collisionNone;
            }

            countEnemyTick = 0;
        }
    }

    showBattleRoom(battleGrid, initGridPos);
    showEntity(player);
    showHud(playerLife, playerSouls);
    screenUpdate();

    if (*playerLife == 0)
    {
        showDialogBox("🧑", "Big Lherme", "jah perdeu?!");
        showDialogBox("🧑", "Big Lherme", "vou lhe dar mais uma chance!");
        playerAddLife(player);
        *playerLife += 1;
    }
    else
    {
        showDialogBox("🧑", "Big Lherme", "voce nao aprendeu nada!");
        showDialogBox("🧑", "Big Lherme", "nunca tera sua alma de volta!!");
        showDialogBox(player->sprite[0], "Nerd", "eh isso que nos veremos!");
    }

    destroyGrid(battleGrid);
    destroyGrid(battleGridCondition);
}

void enemyFourOneLogic(EntityArray *projectsArray, Vector2D *gridVertex, Entity teacherBigLherme)
{
    Vector2D initialProjectsPos[] = {
        /*RIGHT FLAME*/
        {teacherBigLherme.pos.x + 6, teacherBigLherme.pos.y + 1},
        /*TOP FLAME*/
        {teacherBigLherme.pos.x, teacherBigLherme.pos.y - 2},
        /*LEFT FLAME*/
        {teacherBigLherme.pos.x - 6, teacherBigLherme.pos.y + 1}};

    int isProjectsStop = 1;

    for (int i = 0; i < 3; i++)
    {
        Entity *project = &projectsArray->entities[i];

        if (project->pos.y > gridVertex[2].y)
        {
            project->vel.y = 0;
            project->pos.y = initialProjectsPos[i].y;
        }

        if (project->vel.y != 0)
        {
            isProjectsStop = 0;
        }
    }

    if (!isProjectsStop)
    {
        return;
    }

    int random = (rand() % (2 - 0 + 1));

    Entity *project = &projectsArray->entities[random];
    project->vel.y = 3;
}

void initFourTwoBattleRoom(Entity *player, int *playerLife, int *playerSouls)
{

    const int enemyTick = 2;
    int countEnemyTick = 0;

    Entity teacherBigLherme = {
        {MAXX / 2 - 2, MAXY / 2 - 5},
        {0, 0},
        {1, 1},
        {0, bearer},
        {"🧑"},
        WHITE,
        WHITE};

    /*Starting player in grid*/
    Vector2D initGridPos = {teacherBigLherme.pos.x - 6 * 2.5 + 1, teacherBigLherme.pos.y + 3};
    Vector2D initPlayerPos = {initGridPos.x + 2, initGridPos.y + 1};

    // reset entity
    resetEntity(player, initPlayerPos);

    int step = 6;

    /*grid 5x3*/
    Vector2D gridLen = {5, 3};
    BattleGrid *battleGrid = createGrid(gridLen.y, gridLen.x);
    BattleGrid *battleGridCondition = createGrid(gridLen.y, gridLen.x);

    battleGrid->grid[1][1] = condition;
    battleGridCondition->grid[0][1] = setTrue;
    battleGridCondition->grid[1][1] = condition;
    battleGridCondition->grid[2][1] = setFalse;
    battleGridCondition->grid[1][2] = setFalse;

    battleGrid->grid[1][3] = negation;
    battleGridCondition->grid[1][4] = setTrue;

    Vector2D gridVertex[4] = {
        /*topLeft*/
        {initGridPos.x - 2, initGridPos.y - 1},
        /*topRight*/
        {initGridPos.x + (step * gridLen.x), initGridPos.y - 1},
        /*bottomRight*/
        {initGridPos.x + (step * gridLen.x), initGridPos.y + (step / 2 * gridLen.y)},
        /*bottomLeft*/
        {initGridPos.x - 2, initGridPos.y + (step / 2 * gridLen.y)}};

    /* nomeBearer */

    /*Define bearer*/
    Entity bearersContent[6] = {
        // top
        {{initGridPos.x, initGridPos.y - 2},
         {0, 0},
         {step * gridLen.x, 1},
         {0, bearer},
         {"  "},
         WHITE,
         WHITE},
        // right
        {{initGridPos.x + (step * gridLen.x) + 2, initGridPos.y},
         {0, 0},
         {2, (step / 2) * gridLen.y},
         {0, bearer},
         {"  "},
         WHITE,
         WHITE},
        // bottom
        {{initGridPos.x, initGridPos.y + 1 + (step / 2) * gridLen.y},
         {0, 0},
         {step * gridLen.x, 1},
         {0, bearer},
         {"  "},
         WHITE,
         WHITE},
        // left
        {{initGridPos.x - 4, initGridPos.y},
         {0, 0},
         {2, (step / 2) * gridLen.y},
         {0, bearer},
         {"  "},
         WHITE,
         WHITE},
        // red conclusion
        {{gridVertex[1].x, gridVertex[1].y + 4},
         {0, 0},
         {2, 3},
         {0, collisionNone},
         {"⼁"},
         WHITE,
         RED}};

    EntityArray bearersArray = {
        6,
        bearersContent};

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
         WHITE}};

    EntityArray projectsArray = {
        3,
        projectsContent};

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

    showDialogBox(teacherBigLherme.sprite[0], "Big Lherme", "voce nunca passara por essa proposicao!");
    showDialogBox("🧠", "Celebro", "agora eu me lasquei!");
    setSleep(5);

    Action action = actionNone;
    char ch = ' ';

    while (!endBattleCondition(battleGrid, battleGridCondition) && *playerLife > 0)
    {
        if (keyhit())
        {
            ch = readch();
            setEntityVel(player, keyboardVelHandler(ch, step));
            action = keyboardActionHandler(ch);
            checkCollision(player, &bearersArray);
        }

        if (timerTimeOver())
        {
            showHud(playerLife, playerSouls);
            showBattleRoom(battleGrid, initGridPos);

            Vector2D playerGridPos = getGridPos(player, gridVertex, initPlayerPos, step);
            actionRoom(action, battleGrid, playerGridPos);
            if (battleGrid->grid[1][2] == setFalse)
            {
                actionRoom(setTrue, battleGrid, (Vector2D){4,1});
            }
            for (int i = 0; i < 3; i++)
            {
                Vector2D projectGridPos = getGridPos(&projectsContent[i], gridVertex, initPlayerPos, step);
                actionRoom(reset, battleGrid, projectGridPos);
            }

            showEntities(&bearersArray);
            showEntityNoMove(&teacherBigLherme);
            showEntity(player);
            for (int i = 0; i < 3; i++)
            {
                Entity *project = &projectsArray.entities[i];
                showEntityNoMove(project);
            }

            enemyFourOneLogic(&projectsArray, gridVertex, teacherBigLherme);

            // check collision between player and enemy/project
            checkCollision(player, &projectsArray);

            screenUpdate();
            countEnemyTick++;
        }

        if (countEnemyTick == enemyTick)
        {
            for (int i = 0; i < 3; i++)
            {
                Entity *project = &projectsArray.entities[i];
                showEntityNoStop(project);
                screenUpdate();
            }

            if (player->collision.collisionType == damage)
            {
                *playerLife -= 1;
                player->collision.collisionType = collisionNone;
            }

            countEnemyTick = 0;
        }
    }

    showBattleRoom(battleGrid, initGridPos);
    showEntity(player);
    screenUpdate();

    Entity fireBackground = {
        {initGridPos.x, initGridPos.y},
        {0, 0},
        {gridLen.x * step * 2, gridLen.y * (step / 2)},
        {0, collisionNone},
        {"🔥"},
        WHITE,
        WHITE};

    if (*playerLife == 0)
    {
        showDialogBox("🧑", "Big Lherme", "HAHAHA!");
        showDialogBox("🧑", "Big Lherme", "perdeu de novo! nunca tera sua alma de volta!");
    }

    else
    {
        showDialogBox("🧑", "Big Lherme", "NAO PODE SER... voce nao pode...");
        showDialogBox("🧑", "Big Lherme", "VOCE NAO VAI PASSAR!");
    }

    showEntity(&fireBackground);
    showEntity(player);
    screenUpdate();
    setSleep(20);
    showDialogBox("🧑", "Big Lherme", "AGORA VOCE MORRE! HUAHUA");
    showDialogBox("👻", "Reprovados", "NOS VAMOS TE AJUDAR NERD!");
    showDialogBox("🧑", "Big Lherme", "mas o que eh isso?");

    for(int i = 0; i < 4; i++){
        printText("👻", teacherBigLherme.pos.x - step * 1.5 + i * step, teacherBigLherme.pos.y, WHITE, WHITE);
        setSleep(2);
    }

    showDialogBox("🤓", "Nerd", "meus amigos reprovados chegaram!");

    showDialogBox("👻", "Reprovados", "Voce nunca reprovara mais ninguem!");

    for(int i = 0; i < 4; i++){
        printText("  ", teacherBigLherme.pos.x - step * 1.5 + i * step, teacherBigLherme.pos.y, WHITE, WHITE);
    }

    screenUpdate();

    printText("👻", teacherBigLherme.pos.x - 2, teacherBigLherme.pos.y, WHITE, WHITE);
    printText("👻", teacherBigLherme.pos.x - 4, teacherBigLherme.pos.y, WHITE, WHITE);
    printText("👻", teacherBigLherme.pos.x + 2, teacherBigLherme.pos.y, WHITE, WHITE);
    printText("👻", teacherBigLherme.pos.x + 4, teacherBigLherme.pos.y, WHITE, WHITE);
    setSleep(2);
    screenUpdate();

    printText("💥", teacherBigLherme.pos.x + 4, teacherBigLherme.pos.y, WHITE, WHITE);
    printText("💥", teacherBigLherme.pos.x - 4, teacherBigLherme.pos.y, WHITE, WHITE);
    screenUpdate();
    setSleep(1);
    printText("💥", teacherBigLherme.pos.x + 2, teacherBigLherme.pos.y, WHITE, WHITE);
    printText("💥", teacherBigLherme.pos.x - 2, teacherBigLherme.pos.y, WHITE, WHITE);
    screenUpdate();
    setSleep(1);
    showDialogBox("🧑", "Big Lherme", "NAOOOOOO!!");
    printText("💥", teacherBigLherme.pos.x, teacherBigLherme.pos.y, WHITE, WHITE);
    setSleep(2);

    for(int i = 0; i < 5; i++){
        printText("  ", teacherBigLherme.pos.x - 4 + i * 2, teacherBigLherme.pos.y, WHITE, WHITE);
    }

    setSleep(15);
    screenClear();

    showDialogBox("🤓", "Nerd", "finalmente, passei de ano!");

    showDialogBox("⁉️", "Narrador", "agora, o nerd mesmo sem alma!");
    showDialogBox("⁉️", "Narrador", "podera descansar ate o proximo periodo");

    screenClear();

    printText("FIM", MAXX / 2 - 2, MAXY / 2, WHITE, WHITE);
    screenUpdate();
    setSleep(25);

    destroyGrid(battleGrid);
    destroyGrid(battleGridCondition);
}