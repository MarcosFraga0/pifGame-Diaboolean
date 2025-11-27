/**
 * @file start_menu.c
 * @date Nov, 26th 2025
 * @brief start menu game
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ui/start_menu.h"
#include "ui/title.h"

// inital pos draw startOptions
Vector2D initStartMenuPos = {MAXX / 2, (MAXY / 2) * 1.4f };

// startOptions text
char startOptions[3][20] = {
    "Continuar",
    "Novo jogo",
    "Sair do jogo"};

// array startOptions length
const int startOptionsLen = sizeof(startOptions) / sizeof(startOptions[0]);

void startOptionHandler(int selectedOption, int *playerLife, int *playerSouls, int *playerRoom)
{
    switch (selectedOption)
    {
    case 1:
        *playerLife = 3;
        *playerSouls = 1;
        *playerRoom = 1;
        break;
    case 2:
        screenDestroy();
        keyboardDestroy();
        timerDestroy();
        exit(0);
        break;
    default:
        break;
    }
}

/**
 * @brief draw startOptions
 */
void drawstartOptions(int selectedOption)
{
    const int padding = 2;
    showText("diaboolean", (Vector2D){initStartMenuPos.x - 34, initStartMenuPos.y / 4 });

    for (int y = 0; y < startOptionsLen; y++)
    {
        int optionLen = strlen(startOptions[y]);

        // remove star
        printText(" ", initStartMenuPos.x - optionLen / 2 - padding * 2, initStartMenuPos.y + padding * y, WHITE, WHITE);

        // if selected, print star
        if (y == selectedOption)
        {
            printText("⭐", initStartMenuPos.x - optionLen / 2 - padding * 2, initStartMenuPos.y + padding * y, YELLOW, WHITE);
        }

        // text option
        printText(startOptions[y], initStartMenuPos.x - optionLen / 2, initStartMenuPos.y + padding * y, LIGHTGRAY, WHITE);
    }
}

/**
 * @brief start menu
 * @param {int *playerLife} player's life
 * @param {int *playerSouls} player's souls
 * @param {int *playerRoom} player's room
 */
void startMenu(int *playerLife, int *playerSouls, int *playerRoom)
{
    screenInit(1);

    // if click ESC, reset key char
    char ch = 0;
    // index option selected
    int selectedOption = 0;

    // if click ESC again, close menu
    while (1)
    {
        if (keyhit())
        {
            ch = readch();
        }

        if (timerTimeOver())
        {
            switch (tolower(ch))
            {
            // if click ENTER, exec current option handle
            case 10:
                // if click continue
                startOptionHandler(selectedOption, playerLife, playerSouls, playerRoom);
                return;
                break;
            // if click UP, select option above
            case 'w':
                // if index select option > 0, decrement
                // else, do nothing
                selectedOption -= selectedOption > 0 ? 1 : 0;
                break;
            // if click DOWN, select option below
            case 's':
                // if index select option < startOptionsLen, increment
                // else, do nothing
                selectedOption += selectedOption < startOptionsLen - 1 ? 1 : 0;
                break;
            default:
                break;
            }

            ch = 0;

            drawstartOptions(selectedOption);
        }
    }

    ch = 0;

    clearScreen();
    screenInit(1);
}