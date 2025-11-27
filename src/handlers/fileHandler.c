/**
 * @file fileHandler.h
 * @date Nov, 25th 2025
 * @brief file handler
 */

#include "handlers/fileHandler.h"

/**
 * @brief get infos in file
 * @param {int *playerLife}
 * @param {int *playerSouls}
 * @param {int *playerRoom}
 */
void getInfoInFile(int *playerLife, int *playerSouls, int *playerRoom)
{
    FILE *file;

    file = fopen("./info.txt", "r");

    // if file is null, create file
    if (file == NULL)
    {
        return;
    }

    if (fscanf(file, "%d", playerLife) != 1 ||
        fscanf(file, "%d", playerSouls) != 1 ||
        fscanf(file, "%d", playerRoom) != 1)
    {
        return;
    }

    fclose(file);
}

/**
 * @brief set infos in file
 * @param {int *playerLife}
 * @param {int *playerSouls}
 * @param {int *playerRoom}
 */
void setInfoInFile(int *playerLife, int *playerSouls, int *playerRoom)
{
    FILE *file = fopen("./info.txt", "w");
    
    // if file not exists, return
    if (!file)
    {
        return;
    }

    fprintf(file, "%d\n%d\n%d\n", *playerLife, *playerSouls, *playerRoom);

    fclose(file);
}
