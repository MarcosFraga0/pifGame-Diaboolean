/**
 * @file first_room.c
 * @author Matheus de freitas
 * @date Nov, 10th 2025
 * @details first game room
 */


#include <stdio.h>
#include "rooms/first_room.h"

void animationIntro(Entity *player);

/**
 * @brief Init battle room and logic
 * @param {Entity *player} player principal
 * @param {int *playerLife} vida do player
 */
void initFirstRoom(Entity *player, int *playerLife){
    // initial player position
    player->collision.isColliding = 0;
    player->collision.collisionType = collisionNone;
    player->pos.x = MAXX / 2;
    player->pos.y = MAXY - MINY;

    int showPreRoom = 1;

    Entity preRoomContent[] = {
        // door
        {{MAXX / 2, MAXY / 2 + 5},
         {0, 0},
         {1, 1},
         {0, trigger},
         {"🚪"},
         WHITE,
         WHITE},
        // notebook
        {{MAXX / 2 - 16, MAXY / 2 + 2},
         {0,0},
         {1,1},
         {0, bearer},
         {"💻"},
         WHITE, 
         WHITE},
        // bearers
        // top
        {{MAXX / 2 - 20, MAXY / 2 - 5},
         {0, 0},
         {40, 1},
         {0, bearer},
         {"-"},
         WHITE,
         BROWN},
         // bottom
        {{MAXX / 2 - 20, MAXY / 2 + 4},
         {0, 0},
         {40, 1},
         {0, bearer},
         {"-"},
         WHITE,
         BROWN},
        // right
        {{MAXX / 2 + 20, MAXY / 2 - 5},
         {0, 0},
         {1, 10},
         {0, bearer},
         {"⼁"},
         WHITE,
         BROWN},
        // left
        {{MAXX / 2 - 22, MAXY / 2 - 5},
         {0, 0},
         {1, 10},
         {0, bearer},
         {"⼁"},
         WHITE,
         BROWN},
        // notebook
        {{MAXX / 2 - 16, MAXY / 2 - 2},
         {0,0},
         {1,1},
         {0, bearer},
         {"💻"},
         WHITE, 
         WHITE},
        // book
        {{MAXX / 2 + 14, MAXY / 2 - 2},
         {0,0},
         {1,1},
         {0, bearer},
         {"📖"},
         WHITE, 
         WHITE},
        // book
        {{MAXX / 2 + 14, MAXY / 2 + 2},
         {0,0},
         {1,1},
         {0, bearer},
         {"💻"},
         WHITE, 
         WHITE},
         {{MAXX / 2 - 2, MAXY / 2 - 3},
        {0,0},
        {1,1},
        {0, bearer},
        {"🤖"},
        WHITE,
        WHITE},
        /*TEACHER 2 / BIG LHERME*/
        {{MAXX / 2 + 2, MAXY / 2 - 3},
        {0,0},
        {1,1},
        {0, bearer},
        {"🧑"},
        WHITE,
        WHITE}
    };

    Entity *door = &preRoomContent[0];

    int preRoomLen = sizeof(preRoomContent) / sizeof(preRoomContent[0]);
    EntityArray preRoomArray = {preRoomLen, preRoomContent};
    
    Entity roomContent[] = {
        // notebook
        {{MAXX / 2 - 16, MAXY / 2 + 2},
         {0,0},
         {1,1},
         {0, bearer},
         {"💻"},
         WHITE, 
         WHITE},
        // bearers
        // top
        {{MAXX / 2 - 20, MAXY / 2 - 5},
         {0, 0},
         {40, 1},
         {0, bearer},
         {"-"},
         WHITE,
         BROWN},
         // bottom
        {{MAXX / 2 - 20, MAXY / 2 + 4},
         {0, 0},
         {40, 1},
         {0, bearer},
         {"-"},
         WHITE,
         BROWN},
        // right
        {{MAXX / 2 + 20, MAXY / 2 - 5},
         {0, 0},
         {1, 10},
         {0, bearer},
         {"⼁"},
         WHITE,
         BROWN},
        // left
        {{MAXX / 2 - 22, MAXY / 2 - 5},
         {0, 0},
         {1, 10},
         {0, bearer},
         {"⼁"},
         WHITE,
         BROWN},
        // notebook
        {{MAXX / 2 - 16, MAXY / 2 - 2},
         {0,0},
         {1,1},
         {0, bearer},
         {"💻"},
         WHITE, 
         WHITE},
        // book
        {{MAXX / 2 + 14, MAXY / 2 - 2},
         {0,0},
         {1,1},
         {0, bearer},
         {"📖"},
         WHITE, 
         WHITE},
        // book
        {{MAXX / 2 + 14, MAXY / 2 + 2},
         {0,0},
         {1,1},
         {0, bearer},
         {"💻"},
         WHITE, 
         WHITE},
         /*TEACHER 1 / BIG DIG*/
        {{MAXX / 2 - 2, MAXY / 2 - 3},
        {0,0},
        {1,1},
        {0, bearer},
        {"🤖"},
        WHITE,
        WHITE},
        /*TEACHER 2 / BIG LHERME*/
        {{MAXX / 2 + 2, MAXY / 2 - 3},
        {0,0},
        {1,1},
        {0, bearer},
        {"🧑"},
        WHITE,
        WHITE}
    };

    /*👷🥸*/
    int roomContentLen = sizeof(roomContent) / sizeof(roomContent[0]);
    EntityArray roomArray = {roomContentLen, roomContent};

    Entity *notebook = &roomContent[0];    
    Entity *teacherBigDig = &roomContent[8];
    Entity *teacherBigLherme = &roomContent[9];

    /*▄︻デ══━一💥*/

    showEntities(&preRoomArray);
    showEntity(player);
    screenUpdate();

    showDialogBox("🧠", "Celebro", "Puts! Ja estou atrasado.");

    char ch = 0;

    // when player don't collide with notebook
    while (1)
    {
        if (keyhit())
        {
            ch = readch();
            setEntityVel(player, keyboardVelHandler(ch, 2));
            checkCollision(player, showPreRoom ? &preRoomArray : &roomArray);
        }

        if (timerTimeOver() == 1)
        {
            showMenu(&ch);
            showEntities(showPreRoom ? &preRoomArray : &roomArray);
            showEntity(player);
            screenUpdate();

            // if player is collide with door
            if(door->collision.isColliding){
                showPreRoom = 0;
                door->collision.isColliding = 0;
                animationIntro(player);
                showDialogBox("🧑", "Big Lherme", "Todos nos seus lugares! A aula vai comecar.");
                showDialogBox("🧠", "Celebro", "Vou para o meu lugar!");
                notebook->bg = LIGHTGRAY;
            }

            if(teacherBigLherme->collision.isColliding){
                teacherBigLherme->collision.isColliding = 0;
                showDialogBox("🧑", "Big Lherme", "Eu sou Big Lherme, va para o seu lugar para comecarmos!");
            }

            if(teacherBigDig->collision.isColliding){
                teacherBigDig->collision.isColliding = 0;
                showDialogBox("🤖", "Big Dig", "Eu sou Big Dig, vamos comecar.");
            }

            if(notebook->collision.isColliding){
                notebook->collision.isColliding = 0;
                showDialogBox("🧑", "Big Lherme", "Na logica computacional, temos que validar proposicoes para chegarmos a conclusao!");
                showDialogBox("🧑", "Big Lherme", "Isso eh o que chamamos de inferencia");
                showDialogBox("🤖", "Big Dig", "Verdade.");
                break;
            }

        }
    }

    /* explicações de batalha */
    screenClear();
    screenInit(1);
    showEntity(teacherBigLherme);
    screenUpdate();
    showDialogBox("🧑", "Big Lherme", "HEHEHE ...");
    teacherBigLherme->vel.x -= 2;
    teacherBigLherme->vel.y -= 1;
    showEntity(teacherBigLherme);
    screenUpdate();
    setSleep(2);
    teacherBigLherme->vel.x -= 2;
    teacherBigLherme->vel.y -= 1;
    showEntity(teacherBigLherme);
    screenUpdate();
    setSleep(2);
    showDialogBox("🧑", "Big Lherme", "Voce deve estar confuso...");
    showDialogBox("🧑", "Big Lherme", "Deixa eu mostrar como funciona HEHEHE");
    setSleep(5);

    /* battle grid */
    BattleGrid *battleGrid = createGrid(3, 3);
    Vector2D initGridPos = {teacherBigLherme->pos.x - 8, teacherBigLherme->pos.y + 3};
    showBattleRoom(battleGrid, initGridPos);
    screenUpdate();
    showDialogBox("🧑", "Big Lherme", "Essa eh uma grade logica");
    setSleep(5);
   
    player->pos.x = initGridPos.x + 2;
    player->pos.y = initGridPos.y + 1;
    showEntity(player);
    screenUpdate();
    setSleep(10);
    
    printText("  ", player->pos.x, player->pos.y, WHITE, WHITE);
    player->pos.x += 6;
    showEntity(player);
    screenUpdate();
    setSleep(5);
    showDialogBox("🧑", "Big Lherme", "Nela voce pode andar usando WASD");
    printText("  ", player->pos.x, player->pos.y, WHITE, WHITE);
    player->pos.x += 6;
    showEntity(player);
    screenUpdate();
    setSleep(5);
    showDialogBox("🧑", "Big Lherme", "Alem disso, voce consegue colocar valores logicos");
    showDialogBox("🧑", "Big Lherme", "Use a tecla V para verdadeiro");
    battleGrid->grid[0][2] = setTrue; 
    showBattleRoom(battleGrid, initGridPos);
    showEntity(player);
    screenUpdate();
    setSleep(5);

    showDialogBox("🧑", "Big Lherme", "e a tecla F para falso");
    battleGrid->grid[0][1] = setFalse;
    showBattleRoom(battleGrid, initGridPos);
    showEntity(player);
    screenUpdate();
    setSleep(5);

    player->vel.x = 6;
    showEntity(player);
    screenUpdate();
    showDialogBox("🧑", "Big Lherme", "Caso mude de ideia, use a tecla R para resetar");
    battleGrid->grid[0][2] = reset;
    showBattleRoom(battleGrid, initGridPos);
    showEntity(player);
    screenUpdate();
    setSleep(10);

    player->vel.x = -6;
    showEntity(player);
    screenUpdate();
    setSleep(10);
    battleGrid->grid[0][1] = reset;
    showBattleRoom(battleGrid, initGridPos);
    showEntity(player);
    screenUpdate();
    setSleep(10); 
    
    showDialogBox("🧑", "Big Lherme", "o seu objetivo eh validar as proposicoes (linhas e colunas)");
    printText("------", initGridPos.x + 6, initGridPos.y - 1, WHITE, RED);
    printText("⼁", initGridPos.x + 6 * 3, initGridPos.y + 3, WHITE, GREEN);
    printText("⼁", initGridPos.x + 6 * 3, initGridPos.y + 4, WHITE, GREEN);
    printText("⼁", initGridPos.x + 6 * 3, initGridPos.y + 5, WHITE, GREEN);
    screenUpdate();
    showDialogBox("🧑","Big Lherme","correspondendo as conclusoes (valores ao redor da grid)");

    /*LINHA VERMELHA*/
    showDialogBox("🧑", "Big Lherme", "onde vermelho significa que a proposicao deve resultar em falso");
    battleGrid->grid[0][1] = setFalse;
    battleGrid->grid[1][1] = setFalse;
    battleGrid->grid[2][1] = setFalse;
    showBattleRoom(battleGrid, initGridPos);
    showEntity(player);
    screenUpdate();
    setSleep(10);

    /*RESETA LINHA*/
    battleGrid->grid[0][1] = reset;
    battleGrid->grid[1][1] = reset;
    battleGrid->grid[2][1] = reset;
    showBattleRoom(battleGrid, initGridPos);
    showEntity(player);
    screenUpdate();
    setSleep(10);

    /*LINHA VERDE*/
    showDialogBox("🧑", "Big Lherme", "e verde significa que a proposicao deve resultar em verdadeiro");
    battleGrid->grid[1][0] = setTrue;
    battleGrid->grid[1][1] = setTrue;
    battleGrid->grid[1][2] = setTrue;
    showBattleRoom(battleGrid, initGridPos);
    showEntity(player);
    screenUpdate();
    setSleep(10);

    /*// right flame
    printText("🔥", teacherBigLherme->pos.x + 4, teacherBigLherme->pos.y, WHITE, WHITE);
    screenUpdate();
    setSleep(5);
    // top flame
    printText("🔥", teacherBigLherme->pos.x, teacherBigLherme->pos.y - 2, WHITE, WHITE);
    screenUpdate();
    setSleep(5);
    // left flame
    printText("🔥", teacherBigLherme->pos.x - 4, teacherBigLherme->pos.y, WHITE, WHITE);
    screenUpdate();
    setSleep(5); */
}

void animationIntro(Entity *player){
    printText("  ", player->pos.x, player->pos.y, WHITE, WHITE);
    player->pos.y = MAXY / 2 + 3;
    showEntity(player);
    screenUpdate();
}