/**
 * @file four_room.h
 * @author Vinicius Braz (gitviini)
 * @date Nov, 19th 2025
 */
#include "string.h"

#include "rooms/four_room.h"

#define TRAP_TICK 2

void lifeAnimation(Entity *entity);

/**
 * @brief Init four room logic
 * @param {Entity *player} player principal
 * @param {int playerLife} vida do player principal
 */
void initFourRoom(Entity *player, int *playerLife)
{
    // initial player pos and reset player
    Vector2D playerInitialPos = {MINX + 1, MINY + 5};
    resetEntity(player, playerInitialPos);

    // set player steps
    const int playerStep = 2;

    // set don't show secret room and stop trap timer
    int showSecretRoom = 0;
    int trap_timer = 0;

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
            {{0, -10},
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
         {20, MAXY - 7},
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
         {MAXX - 20, MAXY - (MAXY - 10 - MINY)},
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

    // show entities layers
    screenInit(1);
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
            ch = readch();
            setEntityVel(player, keyboardVelHandler(ch, playerStep));
            checkCollision(player, &elementsArray);
            checkCollision(player, showSecretRoom ? &secretBearersArray : &bearersArray);
        }

        if (timerTimeOver())
        {
            // reset char handle
            ch = 0;

            // show elements and player
            showEntities(&elementsArray);
            showEntity(player);
            screenUpdate();

            // if player takes in secret door, show secret room and update entities
            if (elementsContent[2].collision.isColliding == 1)
            {
                showSecretRoom = 1;
                // set life coffee in entity sprite
                strcpy(elementsContent[0].sprite[0], "☕");
                elementsContent[0].bg = WHITE;
                // set secret door as collisionNone
                strcpy(elementsContent[2].sprite[0], " ");
                elementsContent[2].collision.collisionType = collisionNone;

                showEntities(&secretBearersArray);
                showEntities(&elementsArray);
                showEntity(player);
                screenUpdate();
            }

            // if get item, show animation
            if (elementsContent[0].collision.isColliding == 1)
            {
                strcpy(elementsContent[0].sprite[0], " ");
                elementsContent[0].collision.isColliding = 0;
                elementsContent[0].collision.collisionType = collisionNone;

                playerLife++;
                playerAddLife(player);
                screenUpdate();
            }

            // if get item, activate trap
            if (elementsContent[0].collision.collisionType == collisionNone)
            {
                trap_timer++;
            }

            if (trap_timer == TRAP_TICK)
            {
                // set trap
                elementsContent[3].len.y = 1;
                // continua descendo enquanto não chega ao fim da tela
                elementsContent[3].vel.y = elementsContent[3].pos.y < MAXY ? 1 : 0;
                trap_timer = 0;
                checkCollision(player, &elementsArray);
            }

            if (elementsContent[3].collision.isColliding)
            {
                playerLife--;
                playerLoseLife(player);

                // reset room
                initFourRoom(player, playerLife);
                return;
            }
        }
    }
}