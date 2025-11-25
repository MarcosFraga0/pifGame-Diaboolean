/**
 * @file second_battle_room.c
 * @details Battle Room 2: Tutorial do Operador AND (^) com Cutscene da Nariko
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para rand()
#include "rooms/second_battle_room.h"
#include "rooms/battle_room.h"
#include "handlers/timeHandler.h"
#include "handlers/keyboardHandler.h"
#include "handlers/actionRoomHandler.h"
#include "ui/dialog_box.h"
#include "ui/menu.h"

// Configurações da Sala
#define STEP 6
#define FIRE_SPEED 2

// Função auxiliar para a IA da Nariko
void narikoAI(Entity *nariko, Entity *fire, Vector2D minPos, Vector2D maxPos);

void initSecondBattleRoom(Entity *player, int *playerLife)
{
    // --- 1. SETUP INICIAL ---
    
    Vector2D initialGridPos = {MAXX / 2 - 9, MAXY / 2 - 4};
    
    // Grid 3x3
    BattleGrid *battleGrid = createGrid(3, 3);
    BattleGrid *battleGridCondition = createGrid(3, 3);

    // Configuração do Puzzle (AND)
    battleGrid->grid[1][1] = conjunction; 

    // Condição de Vitória (Gabarito): V ^ V = V
    battleGridCondition->grid[1][0] = setTrue; 
    battleGridCondition->grid[1][2] = setTrue; 
    battleGridCondition->grid[2][1] = setTrue;
    battleGridCondition->grid[1][1] = conjunction;

    // Posiciona o Player
    Vector2D initialPlayerPos = {initialGridPos.x + 2, initialGridPos.y + 1};
    resetEntity(player, initialPlayerPos);

    // --- 2. ENTIDADES ---
    
    Entity entities[] = {
        // [0] Fantasma
        {{MAXX/2, initialGridPos.y - 4}, {0,0}, {1,1}, {0, bearer}, {"👻"}, WHITE, WHITE},
        
        // [1] Nariko (Boss)
        {{MAXX - 6, initialGridPos.y + 4}, {0,0}, {1,1}, {0, bearer}, {"👺"}, RED, WHITE},
        
        // [2] Fogo (Projétil)
        {{0, 0}, {0,0}, {1,1}, {0, damage}, {"🔥"}, YELLOW, RED},

        // --- DICAS VISUAIS (Gabarito na Borda) ---
        // Esquerda (Verde - True)
        {{initialGridPos.x - 2, initialGridPos.y + 4}, {0,0}, {1,1}, {0, collisionNone}, {"V"}, WHITE, GREEN},
        // Direita (Verde - True)
        {{initialGridPos.x + (STEP*3) + 1, initialGridPos.y + 4}, {0,0}, {1,1}, {0, collisionNone}, {"V"}, WHITE, GREEN},
        // Baixo (Verde - Resultado True)
        {{initialGridPos.x + STEP + 2, initialGridPos.y + (STEP/2)*3 + 1}, {0,0}, {1,1}, {0, collisionNone}, {"V"}, WHITE, GREEN},
        
        // Paredes invisíveis (Limites)
        {{initialGridPos.x - 4, initialGridPos.y}, {0,0}, {1, 15}, {0, bearer}, {"|"}, WHITE, WHITE},
        {{initialGridPos.x + (STEP*3) + 4, initialGridPos.y}, {0,0}, {1, 15}, {0, bearer}, {"|"}, WHITE, WHITE},
    };
    
    // Ponteiros para facilitar
    Entity *ghost = &entities[0];
    Entity *nariko = &entities[1];
    Entity *fire = &entities[2];
    
    // Calcula tamanho do array automaticamente
    int entitiesCount = sizeof(entities) / sizeof(entities[0]);
    EntityArray entityArray = {entitiesCount, entities};

    // Esconde Nariko e Fogo inicialmente
    nariko->fg = BLACK; 
    nariko->bg = BLACK; 
    strcpy(fire->sprite[0], " "); 

    // --- 3. CUTSCENE ---
    
    screenInit(1);
    showBattleRoom(battleGrid, initialGridPos);
    showEntities(&entityArray); 
    showEntity(player);
    screenUpdate();

    // Diálogo 1
    showDialogBox(player->sprite[0], "Nerd", "Mas que simbolo eh esse??");

    // Fantasma fala
    showEntity(ghost); 
    screenUpdate();
    setSleep(10);
    showDialogBox("👻", "Gasparzinho", "Esse eh o simbolo de conjuncao (^).");

    // Fantasma se move para a esquerda (Tutorial)
    printText(" ", ghost->pos.x, ghost->pos.y, WHITE, WHITE); 
    ghost->pos.x = initialGridPos.x + 2; 
    ghost->pos.y = initialGridPos.y + 4; 
    showEntity(ghost); 
    screenUpdate();
    
    showDialogBox("👻", "Gasparzinho", "Ao colocar valores iguais, resultara em verdadeiro.");

    // Fantasma "digita" na grid
    battleGrid->grid[1][0] = setFalse;
    battleGrid->grid[1][2] = setTrue;
    
    // Simula processamento da lógica
    actionRoomHandler(actionNone, (Vector2D){0,0}, battleGrid);
    
    showBattleRoom(battleGrid, initialGridPos); 
    showEntity(player);
    showEntity(ghost);
    screenUpdate();
    setSleep(15);

    showDialogBox("👻", "Gasparzinho", "Caso os valores sejam diferentes, resultara em falso.");

    // Nariko Aparece
    nariko->fg = RED; 
    nariko->bg = WHITE;
    showEntity(nariko);
    screenUpdate();
    setSleep(10);
    
    showDialogBox("👺", "Nariko", "Achei voce!!! Saia daqui seu reprovaddddoooo!");

    // ANIMAÇÃO DO FOGO
    strcpy(fire->sprite[0], "🔥");
    fire->pos.x = initialGridPos.x + (STEP * 3); 
    fire->pos.y = initialGridPos.y + 4;       

    while(fire->pos.x > initialGridPos.x - 5) {
        printText(" ", fire->pos.x, fire->pos.y, WHITE, WHITE);
        fire->pos.x -= 2; 
        
        // Efeito colateral (Apaga grid)
        if(fire->pos.x < initialGridPos.x + 12) battleGrid->grid[1][2] = reset;
        if(fire->pos.x < initialGridPos.x + 6)  battleGrid->grid[1][1] = reset; 
        if(fire->pos.x < initialGridPos.x)      battleGrid->grid[1][0] = reset;

        showBattleRoom(battleGrid, initialGridPos); 
        showEntity(nariko);
        showEntity(player);
        showEntity(ghost); 
        printText("🔥", fire->pos.x, fire->pos.y, YELLOW, RED);
        
        screenUpdate();
        setSleep(1);
    }
    
    // Mata fantasma
    printText(" ", ghost->pos.x, ghost->pos.y, WHITE, WHITE); 
    strcpy(ghost->sprite[0], " "); 
    ghost->collision.collisionType = collisionNone;
    ghost->pos.x = 0; 
    
    // Restaura grid
    battleGrid->grid[1][1] = conjunction; 
    battleGrid->grid[2][1] = reset;

    screenInit(1);
    showBattleRoom(battleGrid, initialGridPos);
    showEntities(&entityArray);
    showEntity(player);
    screenUpdate();

    showDialogBox("👺", "Nariko", "Agora eh a sua vez de reprovar! muhahaha");

    // --- 4. LOOP JOGÁVEL ---
    
    char ch = 0;
    Action action = actionNone;

    // Define limites para a IA da Nariko
    Vector2D narikoMin = {nariko->pos.x, initialGridPos.y - 2};
    Vector2D narikoMax = {nariko->pos.x, initialGridPos.y + (STEP*3)};

    while (!endBattleCondition(battleGrid, battleGridCondition) && *playerLife > 0)
    {
        if (keyhit())
        {
            ch = readch();
            setEntityVel(player, keyboardVelHandler(ch, STEP));
            action = keyboardActionHandler(ch);
            checkCollision(player, &entityArray); 
        }

        if (timerTimeOver())
        {
            showMenu(&ch); 

            showBattleRoom(battleGrid, initialGridPos);
            Vector2D playerGridPos = getGridPos(player, (Vector2D[]){{0,0}}, initialGridPos, STEP);
            actionRoom(action, battleGrid, playerGridPos);

            // IA da Nariko
            narikoAI(nariko, fire, narikoMin, narikoMax);
            
            // Colisão com Fogo (Check manual)
            if (player->pos.y == fire->pos.y && 
                player->pos.x >= fire->pos.x && player->pos.x <= fire->pos.x + 2) 
            {
                *playerLife -= 1;
                playerLoseLife(player);
                printText(" ", fire->pos.x, fire->pos.y, WHITE, WHITE);
                fire->pos.x = 0; 
            }

            showEntities(&entityArray);
            showEntity(player);
            screenUpdate();
        }
    }

    // --- 5. FIM ---
    
    if (*playerLife > 0) {
        setSleep(10);
        showDialogBox(player->sprite[0], "Nerd", "Ufa... A logica venceu de novo!");
        showDialogBox("👺", "Nariko", "Impossivel! Retirada!");
    } else {
        showDialogBox("👺", "Nariko", "REPROVADOOO!");
    }

    destroyGrid(battleGrid);
    destroyGrid(battleGridCondition);
}

/**
 * @brief IA Simples da Nariko
 */
void narikoAI(Entity *nariko, Entity *fire, Vector2D minPos, Vector2D maxPos) 
{
    // 1. Movimento da Nariko
    if (rand() % 5 == 0) { 
        nariko->vel.y = (rand() % 3) - 1; 
    }
    
    if (nariko->pos.y <= minPos.y) nariko->vel.y = 1;
    if (nariko->pos.y >= maxPos.y) nariko->vel.y = -1;
    
    printText(" ", nariko->pos.x, nariko->pos.y, WHITE, WHITE); 
    nariko->pos.y += nariko->vel.y;

    // 2. Tiro de Fogo
    if (fire->pos.x == 0) {
        if (rand() % 20 == 0) { 
            fire->pos.x = nariko->pos.x - 2;
            fire->pos.y = nariko->pos.y; 
            strcpy(fire->sprite[0], "🔥");
        }
    } else {
        printText(" ", fire->pos.x, fire->pos.y, WHITE, WHITE); 
        fire->pos.x -= FIRE_SPEED;
        
        if (fire->pos.x <= 2) {
            fire->pos.x = 0;
        }
    }
}