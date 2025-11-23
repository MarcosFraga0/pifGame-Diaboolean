/**
 * @file first_room.c
 * @author Matheus de freitas
 * @date Nov, 10th 2025
 * @details first game room
 */


#include <stdio.h>
#include "rooms/first_room.h"

/**
 * @brief Init battle room and logic
 * @param {Entity *player} player principal
 * @param {int *playerLife} vida do player
 */
void initFirstRoom(Entity *player, int *playerLife)
{
    // initial player position
    player->collision.isColliding = 0;
    player->collision.collisionType = collisionNone;
    player->pos.x = 4;
    player->pos.y = 4;

    Entity elements[] = {
        // door
        {{MAXX / 2 - 2, MAXY - 5},
         {0, 0},
         {1, 1},
         {0, bearer},
         {"🚪"},
         WHITE,
         WHITE},
        // bearers
        // top left
        {{MAXX / 2 - 8, MAXY - 5 - 3},
         {0, 0},
         {4, 1},
         {0, bearer},
         {"--"},
         WHITE,
         BROWN},
        // top right
        {{MAXX / 2 + 2, MAXY - 5 - 3},
         {0, 0},
         {4, 1},
         {0, bearer},
         {"--"},
         WHITE,
         BROWN},
        // left
        {{MAXX / 2 + 4, MAXY - 5 - 2},
         {0, 0},
         {2, 5},
         {0, bearer},
         {"⼁"},
         WHITE,
         BROWN},
        // right
        {{MAXX / 2 - 8, MAXY - 5 - 2},
         {0, 0},
         {2, 5},
         {0, bearer},
         {"⼁"},
         WHITE,
         BROWN},
        // bottom
        {{MAXX / 2 - 8, MAXY - 2},
         {0, 0},
         {14, 1},
         {0, bearer},
         {"--"},
         WHITE,
         BROWN},
        // letters
        {{MAXX / 2 - 5, MAXY - 10},
         {0, 0},
         {8, 1},
         {0, collisionNone},
         {"batalha?"},
         BLUE,
         WHITE},
        // keys
        {{MAXX / 2 - 10, MINY + 2},
         {0, 0},
         {20, 2},
         {0, collisionNone},
         {"      W             ",
          "use A S D para mover"},
         LIGHTGRAY,
         WHITE},
        // keys
        {{MAXX / 2 - 14, MINY + 5},
         {0, 0},
         {8, 1},
         {0, collisionNone},
         {"K (true)"},
         GREEN,
         WHITE},
        {{MAXX / 2 - 5, MINY + 5},
         {0, 0},
         {9, 1},
         {0, collisionNone},
         {"L (false)"},
         RED,
         WHITE},
        {{MAXX / 2 + 5, MINY + 5},
         {0, 0},
         {9, 1},
         {0, collisionNone},
         {"J (reset)"},
         BLACK,
         WHITE},
        // keys
        {{MAXX / 2 - 19, MINY + 7},
         {0, 0},
         {39, 2},
         {0, collisionNone},
         {
            "use as teclas acima para igualar blocos", 
            " com as conclusions nas bordas da grid "
          },
         LIGHTGRAY,
         WHITE},
    };

    int entityArrayLen = sizeof(elements) / sizeof(elements[0]);
    EntityArray entityArray = {entityArrayLen, elements};

    showEntities(&entityArray);
    showEntity(player);
    screenUpdate();

    char ch = 0;

    while (entityArray.entities[0].collision.isColliding != 1)
    {
        if (keyhit())
        {
            ch = readch();
            setEntityVel(player, keyboardVelHandler(ch, 2));
            checkCollision(player, &entityArray);
        }

        if (timerTimeOver() == 1)
        {
            showMenu(&ch);
            showEntities(&entityArray);
            showEntity(player);
            screenUpdate();
        }
    }

    showEntities(&entityArray);
    showEntity(player);
    screenUpdate();
}