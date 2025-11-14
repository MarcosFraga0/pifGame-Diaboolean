/**
 * @file timerHandler.h
 * @author Maria Luiza
 * @date Nov, 13th 2025
 * @brief generic time handles
 */

#include "handlers/timeHandler.h"

/**
 * @brief game will be set to sleep for a number ticks
 * @param {int numberTickes} number ticks that will be skipped
 */
void setSleep(int numberTicks){
    int i = 0;
    while(i < numberTicks){
        if(timerTimeOver() == 1){
            i++;
        }
    }
}