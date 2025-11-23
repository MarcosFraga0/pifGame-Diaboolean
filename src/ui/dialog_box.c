/**
 * @file dialog_box.c
 * @author Vinicius Braz (gitviini)
 * @date Nov, 22th 2025
 * @brief dialog box in window bottom
 */

#include <string.h>

#include "ui/dialog_box.h"

const int padding = 2;

// set dialog box props
Vector2D len = {MAXX, MAXY / 2 - (MAXY / 2) / 2 - padding};
Vector2D pos = {MINX, MAXY / 2 + (MAXY / 2) / 2 + padding};

/**
 * @brief draw empty dialog box and border lines
 */
void drawDialogBox()
{
    screenBoxEnable();
    // background
    for (int y = 0; y < len.y + padding / 2; y++)
    {
        for (int x = 0; x < len.x + padding / 2; x++)
        {
            printText(" ", pos.x + x, pos.y + y, WHITE, WHITE);
        }
    }

    // top line
    for (int x = 1; x < len.x; x++)
    {
        screenGotoxy(pos.x + x, pos.y);
        printf("%c", BOX_HLINE);
    }

    // line color
    screenSetColor(WHITE, WHITE);

    // left line
    screenGotoxy(pos.x, pos.y);
    printf("%c", BOX_UPLEFT);
    for (int y = 1; y < len.y; y++)
    {
        screenGotoxy(pos.x, pos.y + y);
        printf("%c", BOX_VLINE);
    }

    // right line
    screenGotoxy(pos.x + len.x, pos.y);
    printf("%c", BOX_UPRIGHT);

    for (int y = 1; y < len.y; y++)
    {
        screenGotoxy(pos.x + len.x, pos.y + y);
        printf("%c", BOX_VLINE);
    }

    // bottom line
    screenGotoxy(pos.x, pos.y + len.y);
    printf("%c", BOX_DWNLEFT);

    for (int x = 1; x < len.x; x++)
    {
        screenGotoxy(pos.x + x, pos.y + len.y);
        printf("%c", BOX_HLINE);
    }

    // bottom line
    screenGotoxy(pos.x + len.x, pos.y + len.y);
    printf("%c", BOX_DWNRIGHT);

    screenUpdate();
    screenBoxDisable();
}

/**
 * @brief clear dialog box (top->bottom) and redraw left, rigth and bottom lines
 */
void clearDialogBox()
{
    screenBoxEnable();
    // clear all box
    for (int y = 0; y < len.y + padding / 2; y++)
    {
        for (int x = 0; x < len.x + padding / 2; x++)
        {
            printText(" ", pos.x + x, pos.y + y, WHITE, WHITE);
        }
    }

    // draw left and right line
    for (int y = 0; y < len.y; y++)
    {
        screenGotoxy(pos.x, pos.y + y);
        printf("%c", BOX_VLINE);

        screenGotoxy(pos.x + len.x, pos.y + y);
        printf("%c", BOX_VLINE);
    }

    // draw bottom line
    for (int x = 0; x < len.x - 1; x++)
    {
        screenGotoxy(pos.x + x, pos.y + len.y);
        printf("%c", BOX_HLINE);
    }
    screenGotoxy(pos.x, pos.y + len.y);
    printf("%c", BOX_DWNLEFT);
    screenGotoxy(pos.x + len.x, pos.y + len.y);
    printf("%c", BOX_DWNRIGHT);

    screenUpdate();
    screenBoxDisable();
}

/**
 * @brief draw entity that is talking
 * @param {char *entitySprite} sprite that will be printed
 * @param {char *entityName} entity's name
 * @param {int nameLen} entity's name length
 */
void drawEntityTalkingBox(char *entitySprite, char *entityName, int nameLen)
{
    printText(entitySprite, pos.x + padding / 2 + nameLen / 2, pos.y + len.y / 2 - padding / 2, LIGHTGRAY, WHITE);
    printText(entityName, pos.x + padding, pos.y + len.y / 2, LIGHTGRAY, WHITE);

    screenBoxEnable();
    // draw division line
    for (int y = 1; y < len.y; y++)
    {
        screenGotoxy(pos.x + nameLen + padding * 2, pos.y + y);
        printf("%c", BOX_VLINE);
    }
    screenUpdate();
    screenBoxDisable();
}

/**
 * @brief typing animation text inside box
 * @param {char *text} text that will be write
 * @param {int nameLen} entity's name length
 */
void typingDialogBox(char *text, int nameLen)
{
    Vector2D textPos = {pos.x + nameLen + padding * 3, pos.y + padding / 2};
    int maxTextLen = len.x - textPos.x - padding;
    int x = 0;
    int y = 0;
    int index = 0;

    while (text[index] != EOF && text[index] != '\0')
    {
        if (maxTextLen == x)
        {
            y++;
            x = 0;
        }

        // põe um "-" antes da palavra se quebrar
        if(maxTextLen - 1 == x && text[index] != ' '){
            printf("-");
            y++;
            x = 0;
        }

        // pula espaço em branco no início da linha
        if(x == 0 && text[index] == ' '){
            index++;
            x++;
        }

        screenGotoxy(textPos.x + x, textPos.y + y);
        screenSetColor(LIGHTGRAY, WHITE);
        printf("%c", text[index]);
        setSleep(1);
        screenUpdate();

        x++;
        index++;
    }
}

/**
 * @brief show dialog box in bottom window
 */
void showDialogBox(char *entitySprite, char *entityName, char *text)
{
    int nameLen = strlen(entityName);

    drawDialogBox();
    drawEntityTalkingBox(entitySprite, entityName, nameLen);
    typingDialogBox(text, nameLen);
    setSleep(20);
    clearDialogBox();
}