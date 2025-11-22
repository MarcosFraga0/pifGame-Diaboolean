/**
 * @file four_room.h
 * @author Vinicius Braz (gitviini)
 * @date Nov, 19th 2025
 */
#include "string.h"

#include "rooms/four_room.h"

void lifeAnimation(Entity *entity);

/**
 * @brief Init four room logic
 * @param {Entity *player} player principal
 */
void initFourRoom(Entity *player)
{
    screenInit(1);
    Vector2D playerInitialPos = {MINX + 1, MINY + 5};
    resetEntity(player, playerInitialPos);
    const int playerStep = 2;
    int showSecretRoom = 0;

    Entity elementsContent[] =
        {
            // life coffee
            {{(MAXX / 2) + (MAXX / 8), playerInitialPos.y},
             {0, 0},
             {1, 1},
             {0, life},
             {"-"},
             WHITE,
             BROWN},
            // door
            {{MAXX - 4, MAXY / 2},
             {0, 0},
             {1, 1},
             {0, bearer},
             {"🚪"},
             WHITE,
             WHITE},
            // secret door (trigger secret room)
            {{MAXX / 2 - 2, playerInitialPos.y},
             {0, 0},
             {1, 1},
             {0, trigger},
             {"🚪"},
             WHITE,
             WHITE},
            // fire trap
            {{0, -20},
             {0, 0},
             {MAXX * 2, 0},
             {0, damage},
             {"🔥"},
             WHITE,
             WHITE},
        };

    int elementsLen = sizeof(elementsContent) / sizeof(elementsContent[0]);

    EntityArray elementsArray = {
        elementsLen,
        elementsContent};

    Entity bearersContent[] = {
        {{MINX, MINY},
         {0, 0},
         {MAXX - MINX, 4},
         {0, bearer},
         {"-"},
         WHITE,
         BROWN},
        {{MINX, 8},
         {0, 0},
         {20, MAXY - 8},
         {0, bearer},
         {"-"},
         WHITE,
         BROWN},
        {{MAXX / 2, MINY + 4},
         {0, 0},
         {(MAXX / 2) / 2, 6},
         {0, bearer},
         {"-"},
         WHITE,
         BROWN},
        {{MAXX / 2 + (MAXX / 2) / 2, MINY + 4},
         {0, 0},
         {(MAXX / 2) / 2, 6},
         {0, bearer},
         {"-"},
         WHITE,
         BROWN},
        {{MINX + 20, MAXY - 9 - MINY},
         {0, 0},
         {MAXX - 20, MAXY - (MAXY - 9 - MINY)},
         {0, bearer},
         {"-"},
         WHITE,
         BROWN},
    };

    int bearersLen = sizeof(bearersContent) / sizeof(bearersContent[0]);

    EntityArray bearersArray = {
        bearersLen,
        bearersContent};

    Entity secretBearersContent[] = {
        bearersContent[0],
        bearersContent[1],
        bearersContent[3],
        bearersContent[4],
        // secret room
        // background
        {{MAXX / 2, MINY + 4},
         {0, 0},
         {(MAXX / 2) / 2, 6},
         {0, collisionNone},
         {" "},
         WHITE,
         WHITE},
        // secret room walls
        // topLeft bearer
        {{MAXX / 2, MINY + 4},
         {0, 0},
         {2, 1},
         {0, bearer},
         {"-"},
         WHITE,
         BROWN},
        // bottomLeft bearer
        {{MAXX / 2, MINY + 4 + 2},
         {0, 0},
         {2, 3},
         {0, bearer},
         {"-"},
         WHITE,
         BROWN},
        // bottomLeftToRight bearer
        {{MAXX / 2, MINY + 3 + 6},
         {0, 0},
         {(MAXX / 2) / 2, 1},
         {0, bearer},
         {"-"},
         WHITE,
         BROWN},
    };

    int secretBearersLen = sizeof(secretBearersContent) / sizeof(secretBearersContent[0]);

    EntityArray secretBearersArray = {
        secretBearersLen,
        secretBearersContent};

    showEntity(player);
    showEntities(&bearersArray);
    showEntities(&elementsArray);
    screenUpdate();

    // enquanto player não chega na porta
    char ch = 0;
    while (!elementsContent[1].collision.isColliding)
    {
        if (keyhit())
        {
            ch = getchar();
            setEntityVel(player, keyboardVelHandler(ch, playerStep));
            checkCollision(player, &elementsArray);
            checkCollision(player, showSecretRoom ? &secretBearersArray : &bearersArray);
        }

        if (timerTimeOver() == 1)
        {
            showEntities(&elementsArray);
            showEntity(player);

            // if get item, update entities
            if (elementsContent[2].collision.isColliding == 1)
            {
                showSecretRoom = 1;
                // set life coffee in entity sprite
                strcpy(elementsContent[0].sprite[0], "☕");
                elementsContent[0].bg = WHITE;
                // set secret door as collisionNone
                elementsContent[2].collision.collisionType = collisionNone;

                showEntities(&secretBearersArray);
                showEntities(&elementsArray);
                showEntity(player);
                screenUpdate();
            }

            // if get item, show animation
            if (elementsContent[0].collision.isColliding == 1)
            {
                strcpy(elementsContent[0].sprite[0], "+♥");
                elementsContent[0].collision.collisionType = collisionNone;
                lifeAnimation(&elementsContent[0]);
            }

            // if get item, activate trap
            if (elementsContent[0].collision.collisionType == collisionNone)
            {
                elementsContent[3].len.y = 1;
                elementsContent[3].vel.y = 1;
            }
        }
    }
}

void lifeAnimation(Entity *entity)
{
    entity->pos.y--;

    entity->fg = RED;
    showEntityNoMove(entity);
    screenUpdate();
    setSleep(5);
    entity->fg = WHITE;
    showEntityNoMove(entity);
    screenUpdate();
    setSleep(5);

    strcpy(entity->sprite[0], "  ");
    showEntityNoMove(entity);
    screenUpdate();
}