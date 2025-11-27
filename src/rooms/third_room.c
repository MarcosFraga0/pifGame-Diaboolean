/**
* @file first_room.c
* @date Nov, 25th 2025
* @details Desk corridor (restore life and catch souls)
*/

#include <stdio.h>
#include "rooms/third_room.h"

void initThirdRoom(Entity *player, int *playerLife, int *playerSouls){
    player->collision.isColliding = 0;
    player->collision.collisionType = collisionNone;
    player->pos.x = MAXX / 2 + 17;
    player->pos.y = MAXY / 2 - 8;

    int showDeskCorridorRoom = 1;

    Entity bearersContent[] = {
        /*TOP PART 1 BEARER*/
        {{MAXX/ 2 - 35, MAXY/2 - 6}, 
        {0, 0},
        {48, 1},
        {0, bearer},
        {"-"},
        WHITE,
        BROWN
        },
        /*BOTTOM PART 1 BEARER*/
        {{MAXX / 2 - 35, MAXY / 2 + 8}, 
        {0, 0},
        {20, 1},
        {0, bearer},
        {"-"},
        WHITE,
        BROWN
        },
        /*BOTTOM PART 1 LEFT BEARER*/
        {{MAXX / 2 - 15, MAXY / 2 + 8},
         {0, 0},
         {2, 3},
         {0, bearer},
         {"⼁"},
         WHITE,
         BROWN},
         /*BOTTOM PART 2 BEARER*/
         {{MAXX / 2 - 15, MAXY / 2 + 11}, 
        {0, 0},
        {16, 1},
        {0, bearer},
        {"-"},
        WHITE,
        BROWN
        },
        /*BOTTOM PART 2 RIGHT BEARER*/
        {{MAXX / 2 - 1, MAXY / 2 + 8},
         {0, 0},
         {2, 3},
         {0, bearer},
         {"⼁"},
         WHITE,
         BROWN},
         /*BOTTOM PART 2 BEARER*/
        {{MAXX / 2 + 1, MAXY / 2 + 8}, 
        {0, 0},
        {28, 1},
        {0, bearer},
        {"-"},
        WHITE,
        BROWN
        },
        /*LEFT BEARER*/
        {{MAXX / 2 - 35, MAXY / 2 - 6},
         {0, 0},
         {2, 15},
         {0, bearer},
         {"⼁"},
         WHITE,
         BROWN},
         /*RIGHT BEARER*/
        {{MAXX / 2 + 29, MAXY / 2 - 6},
         {0, 0},
         {2, 15},
         {0, bearer},
         {"⼁"},
         WHITE,
         BROWN},
         /*TOP PART 2 BEARER*/
        {{MAXX/ 2 + 23, MAXY/2 - 6}, 
        {0, 0},
        {6, 1},
        {0, bearer},
        {"-"},
        WHITE,
        BROWN
        },
        /*TOP LEFT BEARER*/
        {{MAXX / 2 + 21, MAXY / 2 - 10},
         {0, 0},
         {2, 5},
         {0, bearer},
         {"⼁"},
         WHITE,
         BROWN},
         /*TOP RIGHT BEARER*/
        {{MAXX / 2 + 13, MAXY / 2 - 10},
         {0, 0},
         {2, 5},
         {0, bearer},
         {"⼁"},
         WHITE,
         BROWN},
         /*MESAS*/
         // Mesa 1 (topo)
        {{MAXX / 2 + 8, MAXY/2 - 4}, 
         {0, 0}, 
         {2, 4}, 
         {0, bearer},
         {" "}, 
         WHITE, 
         BROWN},
         // Mesa 2 (topo)
        {{MAXX / 2 - 1, MAXY/2 - 4}, 
         {0, 0}, 
         {2, 4}, 
         {0, bearer},
         {" "}, 
         WHITE, 
         BROWN},
         // Mesa 3 (topo)
        {{MAXX / 2 - 10, MAXY/2 - 4}, 
         {0, 0}, 
         {2, 4}, 
         {0, bearer},
         {" "}, 
         WHITE, 
         BROWN},
         // Mesa 4 (topo)
        {{MAXX / 2 - 19, MAXY/2 - 4}, 
         {0, 0}, 
         {2, 4}, 
         {0, bearer},
         {" "}, 
         WHITE, 
         BROWN},
         // Mesa 5 (topo)
        {{MAXX / 2 - 27, MAXY/2 - 4}, 
         {0, 0}, 
         {2, 4}, 
         {0, bearer},
         {" "}, 
         WHITE, 
         BROWN},
         /*ENTITIES*/
                 /*SOUL [16]*/
        {{MAXX / 2 - 31, MAXY / 2 - 4},
         {0, 0},
         {1, 1},
         {0, trigger},
         {"👻"},
         WHITE,
         WHITE},
         /*COFFEE [1]*/
        {{MAXX / 2 - 5, MAXY / 2 + 9},
         {0, 0},
         {1, 1},
         {0, life},
         {"☕"},
         WHITE,
         WHITE},
        /*FIREFIGHTER [2]*/
        {{MAXX / 2 - 11, MAXY / 2 + 9},
         {0, 0},
         {1, 1},
         {0, bearer},
         {"👨‍🚒"},
         WHITE,
         WHITE},
        /*DOOR [3]*/
        {{MAXX / 2 + 17, MAXY / 2 - 10},
         {0, 0},
         {1, 1},
         {0, bearer},
         {"🚪"},
         WHITE,
         WHITE},
         /*STUDENT 1 [4]*/
         {{MAXX / 2 - 17, MAXY / 2 - 1},
         {0, 0},
         {1, 1},
         {0, bearer},
         {"😞"},
         WHITE,
         WHITE},
         /*STUDENT 2 [5]*/
         {{MAXX / 2 - 13, MAXY / 2 - 4},
         {0, 0},
         {1, 1},
         {0, bearer},
         {"😭"},
         WHITE,
         WHITE},
         /*STUDENT 3 [6]*/
         {{MAXX / 2 - 7, MAXY / 2 - 1},
         {0, 0},
         {1, 1},
         {0, bearer},
         {"😥"},
         WHITE,
         WHITE},
    };


    int corridorContentLen = sizeof(bearersContent) / sizeof(bearersContent[0]);
    EntityArray corridorArray = {corridorContentLen, bearersContent};

    /*define entities for collision*/
    Entity *soul = &bearersContent[16];
    Entity *coffee = &bearersContent[17];
    Entity *firefighter = &bearersContent[18];
    Entity *door = &bearersContent[19];
    Entity *student1 = &bearersContent[20];
    Entity *student2 = &bearersContent[21];
    Entity *student3 = &bearersContent[22];
    

    showEntities(&corridorArray);
    screenUpdate();

    char ch = 0;

    // while player don't collide with heart AND soul
    while(1){
        if (keyhit()) {
            ch = readch();
            setEntityVel(player, keyboardVelHandler(ch, 2));
            checkCollision(player, &corridorArray);
            }



        if(timerTimeOver() == 1) {
            showHud(playerLife, playerSouls);
            showMenu(&ch);
            showEntities(&corridorArray);
            showEntity(player);
            screenUpdate();

            if(door->collision.isColliding){
                break;
            }

            if(firefighter->collision.isColliding){
                firefighter->collision.isColliding = 0;
                showDialogBox("👨‍🚒","Bombeiro","Fala chefia! Sem roda de capoeira hoje, por favor.");
            }

            if(student1->collision.isColliding){
                student1->collision.isColliding = 0;
                showDialogBox("😞","Estudante 1","...");
                showDialogBox("🤓","Nerd","Esse parece que ja desistiu");

            }

            if(student2->collision.isColliding){
                student2->collision.isColliding = 0;
                showDialogBox("😭","Estudante 2","Meu Deus, eu vou reprovar!!!");
            }

            if(student3->collision.isColliding){
                student3->collision.isColliding = 0;
                showDialogBox("😥","Estudante 3","Como que eu vou passar?");
            }
            }

            if(coffee->collision.isColliding){
                coffee->collision.isColliding = 0;
                coffee->len.y = 0;
                playerAddLife(player);
                *playerLife += 1;
                screenUpdate();
                
            }

            if(soul->collision.isColliding){
                soul->collision.isColliding = 0;
                showDialogBox("👻","Estudante reprovado","Eu desisti, leve minha alma, por favor.");
                soul->len.y = 0;
                *playerSouls += 1;
                screenUpdate();
            }
        }

    }


