/**
 * @file menu.c
 * @author Vinicius Braz (gitviiini)
 * @date Nov, 10th 2025
 * @details Menu principal do jogo
 */

#include <stdio.h>

#include <string.h>
#include <ctype.h>
#include "ui/menu.h"

// inital pos draw options
Vector2D initialPos = {MAXX / 2, MAXY / 2};

// options text
char options[2][20] = {
    "Continuar",
    "Sair do jogo"
};

// functions that handle options
void (*optionsHandlers[])() = {
    &continueOption,
    &exitGameOption,
};

// array options length
const int optionsLen = sizeof(options) / sizeof(options[0]);

/**
 * @brief draw options
 */
void drawOptions(int selectedOption){
    const int padding = 2;
    printText("PAUSADO", initialPos.x - 3, initialPos.y - padding * 2, WHITE, WHITE);

    for(int y = 0; y < optionsLen; y++){
        int optionLen = strlen(options[y]);
        
        // remove star
        printText(" ", initialPos.x - optionLen / 2 - padding * 2, initialPos.y + padding * y, WHITE, WHITE);

        // if selected, print star
        if(y == selectedOption){
            printText("⭐", initialPos.x - optionLen / 2 - padding * 2, initialPos.y + padding * y, YELLOW, WHITE);
        }

        // text option
        printText(options[y], initialPos.x - optionLen / 2, initialPos.y + padding * y, LIGHTGRAY, WHITE);
    }
}

/**
 * @brief show menu and options
 * @attention NÃO COLOCAR EM BATTLE ROOMs, pois não dá free na grid alocada
 */
void showMenu(char *ch){
    // if don't click ESC, return
    if(*ch != 27){
        return;
    }

    clearScreen();
    screenInit(1);

    // if click ESC, reset key char
    *ch = 0;
    // index option selected
    int selectedOption = 0;

    // if click ESC again, close menu
    while(1){
        if(keyhit()){
            *ch = readch();
        }

        if(timerTimeOver()){
            switch (tolower(*ch))
            {
            // if click ENTER, exec current option handle
            case 10:
                // if click continue
                optionsHandlers[selectedOption]();

                if(selectedOption == 0){
                    return;
                }
                break;
            // if click UP, select option above
            case 'w':
                // if index select option > 0, decrement
                // else, do nothing
                selectedOption -= selectedOption > 0 ? 1 : 0;
                break;
            // if click DOWN, select option below
            case 's':
                // if index select option < optionsLen, increment
                // else, do nothing
                selectedOption += selectedOption < optionsLen - 1 ? 1 : 0;
                break;
            default:
                break;
            }

            *ch = 0;

            drawOptions(selectedOption);
        }
    }

    *ch = 0;

    clearScreen();
    screenInit(1);
}