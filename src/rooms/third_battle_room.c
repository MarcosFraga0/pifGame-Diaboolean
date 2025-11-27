/**
 * @file third_battle_room.h
 * @date Nov, 10th 2025
 * @details second game room
 */

#include <stdio.h>
#include "rooms/third_battle_room.h"

#define ENEMY_TICK 2

void enemyThirdLogic(Entity *enemy, Entity *project, Vector2D *gridVertex, Vector2D playerPos);

/**
 * @brief Init battle room and logic
 * @param {Entity *player} player principal
 * @param {int *playerLife} vida do player
 * @param {int *playerSouls} almas do player
 */
void initThridBattleRoom(Entity *player, int *playerLife, int *playerSouls)
{
    // configs
    Vector2D initialGridPos = {MAXX / 2 - 12, 6};
    Vector2D initial = {initialGridPos.x + 2, initialGridPos.y + 1};
    int step = 6;
    int counterTickEnemy = 0;

    // grid 4x4
    int gridLen = 4;
    BattleGrid *battleGrid = createGrid(gridLen, gridLen);
    BattleGrid *battleGridCondition = createGrid(gridLen, gridLen);

    Vector2D gridVertex[4] = {
        // topLeft
        {initialGridPos.x - 2, initialGridPos.y - 1},
        // topRight
        {initialGridPos.x + (step * gridLen), initialGridPos.y - 1},
        // bottomRight
        {initialGridPos.x + (step * gridLen), initialGridPos.y + (step / 2 * gridLen)},
        // bottomLeft
        {initialGridPos.x - 2, initialGridPos.y + (step / 2 * gridLen)}};

    // initial tile
    battleGrid->grid[1][2] = condition;

    // win condition
    battleGridCondition->grid[1][1] = setTrue;
    battleGridCondition->grid[1][3] = setFalse;
    battleGridCondition->grid[0][2] = setTrue;
    battleGridCondition->grid[2][2] = setFalse;
    battleGridCondition->grid[1][2] = condition;

    // bearers around battle grid
    Entity contentBearers[6] =
        {
            // top
            {{initialGridPos.x, initialGridPos.y - 2},
             {0, 0},
             {step * gridLen, 1},
             {0, bearer},
             {"  "},
             WHITE,
             WHITE},
            // right
            {{initialGridPos.x + (step * gridLen) + 2, initialGridPos.y},
             {0, 0},
             {2, (step / 2) * gridLen},
             {0, bearer},
             {"  "},
             WHITE,
             WHITE},
            // bottom
            {{initialGridPos.x, initialGridPos.y + 1 + (step / 2) * gridLen},
             {0, 0},
             {step * gridLen, 1},
             {0, bearer},
             {"  "},
             WHITE,
             WHITE},
            // left
            {{initialGridPos.x - 4, initialGridPos.y},
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
             GREEN},
            // red conclusion
            {{gridVertex[1].x, gridVertex[1].y + 4},
             {0, 0},
             {2, 3},
             {0, collisionNone},
             {"⼁"},
             WHITE,
             RED},
        };

    // barreiras
    EntityArray bearers = {
        6,
        contentBearers};

    Entity contentEnemies[2] = {
        {{gridVertex[2].x + 2, gridVertex[2].y + 1}, // direita da battle grid
         {0, 0},
         {1, 1},
         {0, collisionNone},
         {"👺"},
         WHITE,
         WHITE},
        {{gridVertex[2].x + 2, gridVertex[2].y - 1},
         {0, 0},
         {1, 1},
         {0, damage},
         {"💥"},
         WHITE,
         WHITE}};

    EntityArray enemies = {
        2,
        contentEnemies};

    // enemy
    Entity *enemy = &enemies.entities[0];

    // enemy's project
    Entity *project = &enemies.entities[1];

    Action action = actionNone;
    char ch = ' ';

    // show text after that start battle
    /* showTextBeforeBattle(); */

    // reset player and set initial position
    resetEntity(player, initial);

    showBattleRoom(battleGrid, initialGridPos);
    // init show game
    screenInit(1);
    printText("🤓", MAXX / 2 - 2, MAXY / 2, WHITE, WHITE);
    printText("👺", MAXX / 2 + 2, MAXY / 2, WHITE, WHITE);
    screenUpdate();

    // dialog pre-battle
    setSleep(5);
    showDialogBox("🧠", "Celebro", "AH NAO, mais um monitor de PIF!!!");
    printText(" ", MAXX / 2 + 2, MAXY / 2, WHITE, WHITE);
    printText("👺", MAXX / 2 + 3, MAXY / 2, WHITE, WHITE);
    screenUpdate();
    setSleep(1);
    printText(" ", MAXX / 2 + 3, MAXY / 2, WHITE, WHITE);
    printText("👺", MAXX / 2 + 1, MAXY / 2, WHITE, WHITE);
    screenUpdate();
    setSleep(2);
    printText(" ", MAXX / 2 + 1, MAXY / 2, WHITE, WHITE);
    printText("👺", MAXX / 2 + 2, MAXY / 2, WHITE, WHITE);
    screenUpdate();
    showDialogBox(enemy->sprite[0], "Monitor de PIF", "Voce nunca vai passar em PIF, JOVEM MANCEBO! HUAHUAHUA");
    printText(" ", MAXX / 2 - 2, MAXY / 2, WHITE, WHITE);
    printText("😓💨", MAXX / 2 - 4, MAXY / 2, WHITE, WHITE);
    screenUpdate();
    showDialogBox(player->sprite[0], "Nerd", "**voce suspira de medo**");

    // loop logic battle room
    while (
        !endBattleCondition(battleGrid, battleGridCondition) && *playerLife > 0)
    {
        if (keyhit())
        {
            ch = readch();
            // set entity vel by key
            setEntityVel(player, keyboardVelHandler(ch, step));
            // get user action by key
            action = keyboardActionHandler(ch);
            // impede o player de sair da grid
            checkCollision(player, &bearers);
        }

        if (timerTimeOver())
        {
            showBattleRoom(battleGrid, initialGridPos);

            // get grid pos
            Vector2D playerGridPos = getGridPos(player, gridVertex, initial, step);
            Vector2D projectGridPos = getGridPos(project, gridVertex, initial, step);

            // apply actions in battleGrid
            actionRoom(action, battleGrid, playerGridPos);
            actionRoom(reset, battleGrid, projectGridPos);

            // show entities
            showEntity(player);
            showEntityNoMove(project);
            showEntities(&bearers);
            showEntityNoMove(enemy);
            showHud(playerLife, playerSouls);

            // check collision between player and enemy/project
            checkCollision(player, &enemies);
            screenUpdate();

            // enemy tick
            counterTickEnemy++;
        }

        if (counterTickEnemy == ENEMY_TICK)
        {
            // if project collide with player, player will lose life point;
            if (player->collision.collisionType == damage)
            {
                *playerLife -= 1;
            }

            showEntityNoStop(project);
            enemyThirdLogic(enemy, project, gridVertex, player->pos);
            counterTickEnemy = 0;
        }
    }

    screenClear();
    screenInit(1);
    screenUpdate();

    if (*playerLife == 0)
    {
        playerLoseLife(player);
        setSleep(5);
        screenUpdate();
        screenClear();
        screenInit(1);
        screenUpdate();
        setSleep(5);
        printText("😵", MAXX / 2 - 2, MAXY / 2, WHITE, WHITE);
        printText("👺", MAXX / 2 + 2, MAXY / 2, WHITE, WHITE);
        screenUpdate();
        showDialogBox("🧠", "Celebro", "Lasquei-me");
        printText(" ", MAXX / 2 + 2, MAXY / 2, WHITE, WHITE);
        printText("👺", MAXX / 2 + 3, MAXY / 2, WHITE, WHITE);
        screenUpdate();
        setSleep(1);
        printText(" ", MAXX / 2 + 3, MAXY / 2, WHITE, WHITE);
        printText("👺", MAXX / 2 + 1, MAXY / 2, WHITE, WHITE);
        screenUpdate();
        setSleep(2);
        printText(" ", MAXX / 2 + 1, MAXY / 2, WHITE, WHITE);
        printText("👺", MAXX / 2 + 2, MAXY / 2, WHITE, WHITE);
        screenUpdate();
        showDialogBox(enemy->sprite[0], "Monitor de PIF", "Voce perdeu! Vai ter que pagar a cadeira de novo HUAHUAHUA");
        clearScreen();
        return;
    }

    else
    {
        // update before the clear screen
        showBattleRoom(battleGrid, initialGridPos);
        Vector2D playerGridPos = getGridPos(player, gridVertex, initial, step);
        actionRoom(action, battleGrid, playerGridPos);
        setSleep(10);
        screenClear();
        screenInit(1);
        screenUpdate();
        setSleep(5);

        printText("🤓", MAXX / 2 - 2, MAXY / 2, WHITE, WHITE);
        screenUpdate();
        printText(" ", MAXX / 2 + 2, MAXY / 2, WHITE, WHITE);
        printText("👺", MAXX / 2 + 3, MAXY / 2, WHITE, WHITE);
        screenUpdate();
        setSleep(1);
        printText(" ", MAXX / 2 + 3, MAXY / 2, WHITE, WHITE);
        printText("👺", MAXX / 2 + 1, MAXY / 2, WHITE, WHITE);
        screenUpdate();
        setSleep(2);
        printText(" ", MAXX / 2 + 1, MAXY / 2, WHITE, WHITE);
        printText("👺", MAXX / 2 + 2, MAXY / 2, WHITE, WHITE);
        screenUpdate();
        showDialogBox(enemy->sprite[0], "Monitor de PIF", "Voce me venceu dessa vez, mas nao passara pelo meu chefe The Big Dig");
        showDialogBox("🧠", "Celebro", "Papo de perdedor hehehe");
    }

    setSleep(10);

    // destroy room grids
    destroyGrid(battleGrid);
    destroyGrid(battleGridCondition);
}

void enemyThirdLogic(Entity *enemy, Entity *project, Vector2D *gridVertex, Vector2D playerPos)
{

    int y = enemy->pos.y;
    int x = enemy->pos.x;

    int step = 2;

    Vector2D enemyPath[4] = {
        {gridVertex[0].x - 2, gridVertex[0].y - 1},
        {gridVertex[1].x + 2, gridVertex[1].y - 1},
        {gridVertex[2].x + 2, gridVertex[2].y + 1},
        {gridVertex[3].x - 2, gridVertex[3].y + 1},
    };

    Vector2D initial = enemyPath[0];
    Vector2D velocities[4] = {
        // topLeft to bottomLeft
        {0, step / 2},
        // topRight to topLeft
        {-step, 0},
        // bottomRight to topRight
        {0, -step / 2},
        // bottomLeft to bottomRight
        {step, 0},
    };

    // se estiver fora, a velocidade para
    if (!(project->pos.x > enemyPath[0].x && project->pos.x < enemyPath[2].x && project->pos.y > enemyPath[0].y && project->pos.y < enemyPath[2].y))
    {
        project->vel.x = 0;
        project->vel.y = 0;
    }
    if (x == playerPos.x)
    {
        project->vel.x = 0;
        project->vel.y = y > playerPos.y ? -3 : 3;
        project->pos.y = y == initial.y ? y + 3 : y - 3;
        project->pos.x = playerPos.x;
    }

    else if (y == playerPos.y)
    {
        project->vel.y = 0;
        project->vel.x = x > playerPos.x ? -6 : 6;
        project->pos.y = playerPos.y;
        project->pos.x = x == initial.x ? x + 6 : x - 6;
    }

    for (int i = 0; i < 4; i++)
    {
        if (enemyPath[i].x == enemy->pos.x && enemyPath[i].y == enemy->pos.y)
        {
            enemy->vel.x = velocities[i].x;
            enemy->vel.y = velocities[i].y;
        }
    }

    showEntityNoStop(enemy);
}