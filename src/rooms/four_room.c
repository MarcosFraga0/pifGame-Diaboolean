/**
 * @file four_room.h
 * @date Nov, 19th 2025
 */

#include "string.h"

#include "rooms/four_room.h"

/**
 * @brief Init four room logic
 * @param {Entity *player} player principal
 * @param {int *playerLife} vida do player principal
 * @param {int *playerSouls} almas do player principal
 */
void initFourRoom(Entity *player, int *playerLife, int *playerSouls)
{
    // init positions
    Vector2D roomSize = {50, 14};
    Vector2D initRoomPos = {MAXX / 2 - roomSize.x / 2, MAXY / 2 - roomSize.y / 2};
    Vector2D initPlayerPos = {initRoomPos.x + roomSize.x - roomSize.x / 4 + 2, initRoomPos.y + roomSize.y - 1};
    int step = 2;

    Entity roomContent[] = {
        /* ELEMENTS */
        // door
        {
            {initRoomPos.x + roomSize.x - 2, initRoomPos.y + 2},
            {0, 0},
            {1, 1},
            {0, bearer},
            {"🚪"},
            WHITE,
            WHITE
        },
        // student (topLeft)
        {
            {initRoomPos.x + roomSize.x / 6, initRoomPos.y + 3},
            {0, 0},
            {1, 1},
            {0, bearer},
            {"🤧"},
            WHITE,
            WHITE
        },
        // student (bottomLeft)
        {
            {initRoomPos.x + 4, initRoomPos.y + roomSize.y - 4},
            {0, 0},
            {1, 1},
            {0, bearer},
            {"😪"},
            WHITE,
            WHITE
        },
        // soul (bottomLeft)
        {
            {initRoomPos.x + 8, initRoomPos.y + roomSize.y - 2},
            {0, 0},
            {1, 1},
            {0, bearer},
            {"👻"},
            WHITE,
            WHITE
        },
        // soul (middleTopLeft)
        {
            {initRoomPos.x + roomSize.x / 2 - 7, initRoomPos.y + roomSize.y / 2 - 1},
            {0, 0},
            {1, 1},
            {0, bearer},
            {"👻"},
            WHITE,
            WHITE
        },
        // soul (middleTopRight)
        {
            {initRoomPos.x + roomSize.x / 2 - 1, initRoomPos.y + roomSize.y / 2 - 1},
            {0, 0},
            {1, 1},
            {0, bearer},
            {"👻"},
            WHITE,
            WHITE
        },
        /* BEARERS */
        // top
        {
            {initRoomPos.x, initRoomPos.y},
            {0, 0},
            {roomSize.x, 1},
            {0, bearer},
            {"-"},
            WHITE,
            BROWN,
        },
        // bottom
        {
            {initRoomPos.x, initRoomPos.y + roomSize.y},
            {0, 0},
            {roomSize.x, 1},
            {0, bearer},
            {"-"},
            WHITE,
            BROWN,
        },
        // bottom
        {
            {initRoomPos.x + roomSize.x - roomSize.x / 4 , initRoomPos.y + roomSize.y},
            {0, 0},
            {roomSize.x / 8, 1},
            {0, bearer},
            {"-"},
            WHITE,
            WHITE,
        },
        // left
        {
            {initRoomPos.x, initRoomPos.y},
            {0, 0},
            {2, roomSize.y + 1},
            {0, bearer},
            {"⼁"},
            WHITE,
            BROWN,
        },
        // left
        {
            {initRoomPos.x, initRoomPos.y + roomSize.y / 2 - roomSize.y / 8},
            {0, 0},
            {2, roomSize.y / 4},
            {0, bearer},
            {"⼁"},
            WHITE,
            WHITE,
        },
        // right
        {
            {initRoomPos.x + roomSize.x, initRoomPos.y},
            {0, 0},
            {2, roomSize.y + 1},
            {0, bearer},
            {"⼁"},
            WHITE,
            BROWN,
        },
        /* PUFFS */
        // puff (middleLeft)
        {
            {initRoomPos.x + roomSize.x / 2 - 7, initRoomPos.y + roomSize.y / 2},
            {0, 0},
            {4, 2},
            {0, bearer},
            {". "},
            WHITE,
            MAGENTA
        },
        // puff (middleRight)
        {
            {initRoomPos.x + roomSize.x / 2 - 1, initRoomPos.y + roomSize.y / 2},
            {0, 0},
            {4, 2},
            {0, bearer},
            {". "},
            WHITE,
            RED
        },
        /* TABLES */
        // mesa (topLeft)
        {
            {initRoomPos.x + 4, initRoomPos.y + 2},
            {0, 0},
            {4, 2},
            {0, bearer},
            {" "},
            WHITE,
            MAGENTA
        },
        // pe da mesa
        {
            {initRoomPos.x + 4, initRoomPos.y + 4},
            {0, 0},
            {4, 1},
            {0, collisionNone},
            {"ˈ  ˈ"},
            LIGHTGRAY,
            WHITE
        },
        // mesa (bottomLeft)
        {
            {initRoomPos.x + 4, initRoomPos.y + roomSize.y - 3},
            {0, 0},
            {4, 2},
            {0, bearer},
            {" "},
            WHITE,
            BROWN
        },
        // pe da mesa
        {
            {initRoomPos.x + 4, initRoomPos.y + roomSize.y - 1},
            {0, 0},
            {4, 1},
            {0, collisionNone},
            {"ˈ  ˈ"},
            LIGHTGRAY,
            WHITE
        },
        // coffee
        {
            {initRoomPos.x + roomSize.x / 8 + 2, initRoomPos.y + 2},
            {0, 0},
            {1, 1},
            {0, trigger},
            {"☕"},
            WHITE,
            WHITE
        },
    };

    int roomContentLen = sizeof(roomContent) / sizeof(roomContent[0]);

    Entity *door = &roomContent[0];

    char studentsDialogs[2][100] = {
        "Estou doente, nao vou fazer prova hoje!",
        "Bem que podia ter prostesto na prefeitura hoje?!",
    };
    Entity *students[] = {
        &roomContent[1],
        &roomContent[2],
    };

    char soulsDialogs[3][100] = {
        "Desisto de PIF, leve minha alma com voce!",
        "Nao tomei cafe e olha no que deu?!",
        "Nao entendo Logica! por favor me ajude!"
    };
    Entity *souls[] = {
        &roomContent[3],
        &roomContent[4],
        &roomContent[5],
    };

    Entity *coffee = &roomContent[roomContentLen - 1];

    EntityArray roomArray = {
        roomContentLen,
        roomContent};

    resetEntity(player, initPlayerPos);

    showEntities(&roomArray);
    showEntity(player);

    char ch = 0;

    while (1)
    {
        if (keyhit())
        {
            ch = readch();
            setEntityVel(player, keyboardVelHandler(ch, step));
            checkCollision(player, &roomArray);
        }

        if (timerTimeOver())
        {
            showMenu(&ch);
            showHud(playerLife, playerSouls);

            showEntities(&roomArray);
            showEntity(player);

            // door
            if(door->collision.isColliding){
                break;
            }

            // coffee
            if(coffee->collision.isColliding){
                coffee->len.y = 0;
                coffee->collision.isColliding = 0;
                *playerLife += 1;
                playerAddLife(player);
                showDialogBox(students[0]->sprite[0], "Bolsista", "Ei! Nao tome meu cafe!");
            }

            // students
            for(int i = 0; i < 2; i++){
                if(students[i]->collision.isColliding){
                    students[i]->collision.isColliding = 0;
                    showDialogBox(students[i]->sprite[0], "Bolsista", studentsDialogs[i]);
                }
            }

            // souls
            for(int i = 0; i < 3; i++){
                if(souls[i]->collision.isColliding){
                    souls[i]->collision.isColliding = 0;
                    showDialogBox(souls[i]->sprite[0], "Desistente", soulsDialogs[i]);
                    souls[i]->len.y = 0;
                    printText("  ", souls[i]->pos.x, souls[i]->pos.y, WHITE, WHITE);
                    *playerSouls += 1;
                    playerAddSoul(player);
                }
            }
        }
    }
}