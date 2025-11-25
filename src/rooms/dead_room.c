/**
 * @file dead_room.h
 * @author Vinicius Braz (gitviini)
 * @date Nov, 25th 2025
 * @brief dead's room
 */

#include <string.h>
#include <stdlib.h>
#include "rooms/dead_room.h"

void initDeadRoom(Entity *player, int *playerLife, int *playerSouls)
{
    Vector2D initPlayerPos = {MAXX / 2, MAXY / 2};
    strcpy(player->sprite[0], "👻");
    int step = 2;

    resetEntity(player, initPlayerPos);

    screenColor bearersBgColor = LIGHTGRAY;

    Entity roomContent[] = {
        {{MAXX / 2, MAXY / 2 + 3},
         {0, 0},
         {1, 0},
         {0, trigger},
         {"🚪"},
         WHITE,
         WHITE},
        {{MAXX / 2 - 16, MAXY / 2 - 1},
         {0, 0},
         {1, 1},
         {0, bearer},
         {"👻"},
         WHITE,
         WHITE},
        {{MAXX / 2 + 14, MAXY / 2 - 1},
         {0, 0},
         {1, 1},
         {0, bearer},
         {"🎃"},
         WHITE,
         WHITE},
        {{MAXX / 2 + 14, MAXY / 2 + 3},
         {0, 0},
         {1, 1},
         {0, bearer},
         {"💀"},
         WHITE,
         WHITE},
        // notebook
        {{MAXX / 2 - 20, MAXY / 2 - 4},
         {0, 0},
         {1, 8},
         {0, collisionNone},
         {"🔥"},
         RED,
         WHITE},
        {{MAXX / 2 + 18, MAXY / 2 - 4},
         {0, 0},
         {1, 8},
         {0, collisionNone},
         {"🔥"},
         RED,
         WHITE},
        // notebook
        {{MAXX / 2 - 16, MAXY / 2 + 2},
         {0, 0},
         {1, 1},
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
         bearersBgColor},
        // bottom
        {{MAXX / 2 - 20, MAXY / 2 + 4},
         {0, 0},
         {40, 1},
         {0, bearer},
         {"-"},
         WHITE,
         bearersBgColor},
        // right
        {{MAXX / 2 + 20, MAXY / 2 - 5},
         {0, 0},
         {1, 10},
         {0, bearer},
         {"⼁"},
         WHITE,
         bearersBgColor},
        // left
        {{MAXX / 2 - 22, MAXY / 2 - 5},
         {0, 0},
         {1, 10},
         {0, bearer},
         {"⼁"},
         WHITE,
         bearersBgColor},
        // notebook
        {{MAXX / 2 - 16, MAXY / 2 - 2},
         {0, 0},
         {1, 1},
         {0, bearer},
         {"💻"},
         WHITE,
         WHITE},
        // book
        {{MAXX / 2 + 14, MAXY / 2 - 2},
         {0, 0},
         {1, 1},
         {0, bearer},
         {"📖"},
         WHITE,
         WHITE},

        // book
        {{MAXX / 2 + 14, MAXY / 2 + 2},
         {0, 0},
         {1, 1},
         {0, bearer},
         {"💻"},
         WHITE,
         WHITE},

        /*TEACHER 1 / BIG DIG*/
        {{MAXX / 2 - 2, MAXY / 2 - 3},
         {0, 0},
         {1, 1},
         {0, life},
         {"☕"},
         WHITE,
         WHITE},
        /*TEACHER 2 / BIG LHERME*/
        {{MAXX / 2 + 2, MAXY / 2 - 3},
         {0, 0},
         {1, 1},
         {0, life},
         {"☕"},
         WHITE,
         WHITE}};

    int roomContentLen = sizeof(roomContent) / sizeof(roomContent[0]);
    EntityArray roomArray = {
        roomContentLen,
        roomContent};

    Entity *coffees[] = {
        &roomContent[roomContentLen - 2],
        &roomContent[roomContentLen - 1],
    };

    Entity *students[] = {
        &roomContent[1],
        &roomContent[2],
        &roomContent[3]
    };

    char studentsDialogs[3][41] = {
        "Meu deus, cafe eh bom demais!",
        "Onde esta o Big Dig?",
        "Odeio PIF...",
    };

    Entity *door = &roomContent[0];

    Entity death = {
        {MAXX / 2 - 1, MINY + 3},
        {0, 0},
        {1, 1},
        {0, collisionNone},
        {"🗡️ 💀"},
        WHITE,
        WHITE};

    *playerLife = 0;

    screenClear();
    screenInit(1);
    showEntities(&roomArray);
    showEntity(&death);
    showEntity(player);
    showHud(playerLife, playerSouls);
    showDialogBox("🧠", "Celebro", "que lugar eh esse? onde eu estou?");
    showDialogBox("🗡️ 💀", "Morte", "voce esta no 12~ mundo dos mortos");
    showDialogBox("👻", "Nerd reprovado", "mas por que?");
    printText("     ", death.pos.x, death.pos.y, WHITE, WHITE);
    death.vel.x = -2;
    showEntity(&death);
    screenUpdate();
    setSleep(1);
    printText("     ", death.pos.x, death.pos.y, WHITE, WHITE);
    death.vel.x = +4;
    showEntity(&death);
    screenUpdate();
    setSleep(1);
    printText("     ", death.pos.x, death.pos.y, WHITE, WHITE);
    death.vel.x = -2;
    showEntity(&death);
    screenUpdate();
    setSleep(1);
    showDialogBox("🗡️ 💀", "Morte", "deixe de fazer perguntas!!");
    showDialogBox("🗡️ 💀", "Morte", "voce reprovou e todos os reprovados perdem a vida");
    showDialogBox("🗡️ 💀", "Morte", "e a alma...");

    showDialogBox("🧠", "Celebro", "olha! cafe! eu quero cafeee!!!");

    char ch = 0;

    while (!door->collision.isColliding)
    {
        if (keyhit())
        {
            ch = readch();
            setEntityVel(player, keyboardVelHandler(ch, step));
            checkCollision(player, &roomArray);
            checkCollision(player, &roomArray);
        }

        if (timerTimeOver())
        {
            showMenu(&ch);
            showEntities(&roomArray);
            showEntity(door);
            showEntity(&death);
            showEntity(player);
            showHud(playerLife, playerSouls);

            for (int i = 0; i < 2; i++)
            {
                if (coffees[i]->collision.isColliding)
                {
                    *playerLife += 1;
                    playerAddLife(player);
                    coffees[i]->collision.isColliding = 0;
                    coffees[i]->len.y = 0;

                    if (*playerLife == 1)
                    {
                        strcpy(player->sprite[0], "🤓");
                        door->len.y = 1;
                        showEntity(door);
                        showDialogBox("🧠", "Celebro", "uma porta??");
                        showDialogBox("🗡️ 💀", "Morte", "o cafe recupera sua vida, mas nao sua alma");
                        showDialogBox("🗡️ 💀", "Morte", "AGORA VOCE ESTA VIVO, e deve SAIR do mundo dos mortos!");
                    }
                }
            }

            for(int i = 0; i < 3; i++){
                if(students[i]->collision.isColliding){
                    students[i]->collision.isColliding = 0;
                    showDialogBox(students[i]->sprite[0], "reprovado", studentsDialogs[i]);
                }
            }
        }
    }

    clearScreen();
}