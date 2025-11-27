/**
 * @file second_battle_room.c
 * @details Tutorial do Operador AND (^) com Cutscene da Nariko
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Necessário para rand()

// --- INCLUDES OBRIGATÓRIOS ---
#include "rooms/second_battle_room.h"
#include "rooms/battle_room.h"
#include "entities/entity.h"
#include "handlers/keyboardHandler.h"
#include "handlers/actionRoomHandler.h"
#include "handlers/timeHandler.h"
#include "handlers/screenHandler.h"
#include "ui/dialog_box.h"
#include "ui/menu.h"
#include "ui/hud.h"
#include "screen.h"
#include "keyboard.h"
#include "animations/player.h"

#define FIRE_SPEED 2

// Função auxiliar para o tiro da Nariko
void narikoShooting(Entity *nariko, Entity *fire, int limitX);

void initSecondBattleRoom(Entity *player, int *playerLife, int *playerSouls)
{
    // --- 1. CONFIGURAÇÕES ---
    Vector2D initialGridPos = {MAXX / 2 - 9, MAXY / 2 - 4};
    // Define step internamente
    const int step = 6;
    
    // Grid 3x3
    int gridLen = 3;
    BattleGrid *battleGrid = createGrid(gridLen, gridLen);
    BattleGrid *battleGridCondition = createGrid(gridLen, gridLen);

    // Configuração do Puzzle (AND)
    battleGrid->grid[1][1] = conjunction; 

    // Condição de Vitória (Vertical: Cima ^ Baixo -> Direita)
    battleGridCondition->grid[1][0] = setTrue;  // Input 1 (Cima)
    battleGridCondition->grid[1][2] = setTrue;  // Input 2 (Baixo)
    battleGridCondition->grid[2][1] = setTrue;  // Output (Direita)
    battleGridCondition->grid[1][1] = conjunction;

    // Vértices da Grid (4 pontos)
    Vector2D gridVertex[4] = {
        {initialGridPos.x - 2, initialGridPos.y - 1},
        {initialGridPos.x + (step * gridLen), initialGridPos.y - 1},
        {initialGridPos.x + (step * gridLen), initialGridPos.y + (step / 2 * gridLen)},
        {initialGridPos.x - 2, initialGridPos.y + (step / 2 * gridLen)}
    };

    // Reset Player
    Vector2D initialPlayerPos = {initialGridPos.x + 2, initialGridPos.y + 1};
    resetEntity(player, initialPlayerPos);

    // --- 2. ENTIDADES ---
    
    // Paredes Visuais (Bearers) ao redor da grid
    // IMPORTANTE: Removi as paredes laterais invisíveis que travavam o jogador
    // Mantive apenas as visuais "decorativas" ou limites extremos
    Entity contentBearers[] = {

        // --- DICAS VISUAIS (Verdes) ---
        // Topo (Alinhado com a coluna do meio [2][2])
        {{initialGridPos.x + step, initialGridPos.y + (step / 2) * 3}, {0,0}, {step, 1}, {0, collisionNone}, {"-"}, WHITE, GREEN},
    };
    
    int bearersLen = sizeof(contentBearers) / sizeof(contentBearers[0]);
    EntityArray bearers = {bearersLen, contentBearers};

    // Inimigos e NPCs
    Entity contentEnemies[] = {
        // [0] Fantasma
        {{MAXX/2, initialGridPos.y - 4}, {0,0}, {1,1}, {0, bearer}, {"👻"}, WHITE, WHITE},
        // [1] Nariko (Boss)
        {{MAXX - 6, initialGridPos.y + 4}, {0,0}, {1,1}, {0, bearer}, {" "}, RED, WHITE}, 
        // [2] Fogo (Projétil)
        {{-10, -10}, {0,0}, {1,1}, {0, damage}, "🔥", YELLOW, WHITE}
    };
    
    int enemiesLen = sizeof(contentEnemies) / sizeof(contentEnemies[0]);
    EntityArray enemies = {enemiesLen, contentEnemies};

    Entity *ghost = &contentEnemies[0];
    Entity *nariko = &contentEnemies[1];
    Entity *fire = &contentEnemies[2];

    // Esconde fogo
    strcpy(fire->sprite[0], " "); 

    Action action = actionNone;
    char ch = ' ';

    // --- 3. CUTSCENE ---
    
    screenInit(1);
    showBattleRoom(battleGrid, initialGridPos);
    showEntities(&bearers);
    showEntity(player);
    screenUpdate();

    showDialogBox(player->sprite[0], "Nerd", "Mas que simbolo eh esse??");

    showEntity(ghost); 
    screenUpdate();
    setSleep(10);
    showDialogBox("👻", "Gasparzinho", "Esse eh o simbolo de conjuncao (^).");

    // Fantasma move
    printText("  ", ghost->pos.x, ghost->pos.y, WHITE, WHITE); 
    ghost->pos.x = initialGridPos.x + 2; 
    ghost->pos.y = initialGridPos.y + 4; 
    showEntity(ghost); 
    screenUpdate();
    
    showDialogBox("👻", "Gasparzinho", "Ao colocar valores iguais, resultara em verdadeiro.");

    // Demonstração
    battleGrid->grid[1][0] = setTrue;
    battleGrid->grid[1][2] = setTrue;
    
    // Força atualização visual da grid
    showBattleRoom(battleGrid, initialGridPos);
    showEntity(player);
    showEntity(ghost);
    screenUpdate();
    setSleep(15);

    battleGrid->grid[2][1] = setTrue;
    showBattleRoom(battleGrid, initialGridPos);
    showEntity(player);
    showEntity(ghost);
    screenUpdate();
    setSleep(15);

    showDialogBox("👻", "Gasparzinho", "Caso os valores sejam diferentes, resultara em falso.");

    battleGrid->grid[1][0] = setFalse;
    showBattleRoom(battleGrid, initialGridPos);
    showEntity(player);
    showEntity(ghost);
    screenUpdate();
    setSleep(15);
    battleGrid->grid[2][1] = setFalse;
    showBattleRoom(battleGrid, initialGridPos);
    showEntity(player);
    showEntity(ghost);
    screenUpdate();
    setSleep(15);

    // Nariko Aparece
    strcpy(nariko->sprite[0], "👺");
    showEntity(nariko);
    screenUpdate();
    setSleep(10);
    
    showDialogBox("👺", "Nariko", "Achei voce!!! Saia daqui seu reprovaddddoooo!");

    // Animação do Fogo da Cutscene
    strcpy(fire->sprite[0], "🔥");
    fire->pos.x = initialGridPos.x + (step * 3); 
    fire->pos.y = initialGridPos.y + 4;       

    // Move até a borda esquerda da grid
    int limitX = initialGridPos.x - 2;

    while(fire->pos.x > limitX) {
        printText("  ", fire->pos.x, fire->pos.y, WHITE, WHITE); // Limpa rastro
        fire->pos.x -= 2; 
        
        // Apaga grid ao passar
        if(fire->pos.x < initialGridPos.x + 12) battleGrid->grid[1][2] = reset;
        if(fire->pos.x < initialGridPos.x + 6)  battleGrid->grid[1][1] = reset; 
        if(fire->pos.x < initialGridPos.x)      battleGrid->grid[1][0] = reset;

        showBattleRoom(battleGrid, initialGridPos); 
        showEntity(nariko);
        showEntity(player);
        showEntity(ghost); 
        
        if(fire->pos.x > limitX) 
            printText("🔥", fire->pos.x, fire->pos.y, YELLOW, RED);
        
        screenUpdate();
        setSleep(1);
    }
    
    // Mata fantasma
    printText("  ", ghost->pos.x, ghost->pos.y, WHITE, WHITE); 
    strcpy(ghost->sprite[0], " "); 
    ghost->collision.collisionType = collisionNone;
    ghost->pos.x = 0; 
    
    // Restaura grid
    battleGrid->grid[1][1] = conjunction; 
    battleGrid->grid[2][1] = reset;

    screenInit(1);
    showBattleRoom(battleGrid, initialGridPos);
    showEntities(&bearers); // Paredes voltam
    showEntity(nariko);
    showEntity(player);
    screenUpdate();

    showDialogBox("👺", "Nariko", "Agora eh a sua vez de reprovar! muhahaha");

    // --- 4. LOOP JOGÁVEL ---
    
    int limitFireX = initialGridPos.x - 2; // Limite esquerdo da grid

    while (!endBattleCondition(battleGrid, battleGridCondition) && *playerLife > 0)
    {
        if (keyhit())
        {
            ch = readch();
            setEntityVel(player, keyboardVelHandler(ch, step));
            action = keyboardActionHandler(ch);
            checkCollision(player, &bearers); // Colide com as paredes
        }

        if (timerTimeOver())
        {
            showMenu(&ch); 
            showHud(playerLife, playerSouls);
            showBattleRoom(battleGrid, initialGridPos);
            
            Vector2D playerGridPos = getGridPos(player, gridVertex, initialPlayerPos, step);
            
            actionRoom(action, battleGrid, playerGridPos);

            // Lógica do Tiro
            narikoShooting(nariko, fire, limitFireX);
            
            // Colisão com Fogo
            if (player->pos.y == fire->pos.y && 
                player->pos.x >= fire->pos.x && player->pos.x <= fire->pos.x + 2) 
            {
                *playerLife -= 1;
                playerLoseLife(player);
                printText("  ", fire->pos.x, fire->pos.y, WHITE, WHITE);
                fire->pos.x = -10; 
            }

            showEntities(&bearers);
            showEntityNoMove(nariko); // Nariko estática
            showEntity(player);
            screenUpdate();
        }
    }

    showBattleRoom(battleGrid, initialGridPos);
    showEntities(&bearers);
    showEntityNoMove(nariko);
    showEntity(player);
    screenUpdate();
    setSleep(10);

    // --- 5. FIM ---
    if (*playerLife > 0) {
        setSleep(10);
        showDialogBox(player->sprite[0], "Nerd", "Ufa... A logica venceu de novo!");
        showDialogBox("👺", "Nariko", "Impossivel! Retirada!");
    } else {
        showDialogBox("👺", "Nariko", "REPROVADOOO!");
        // Reinicia a sala (recursão controlada para retry)
        // initSecondBattleRoom(player, playerLife); // Opcional: Reiniciar ao perder
    }

    destroyGrid(battleGrid);
    destroyGrid(battleGridCondition);
}

/**
 * @brief Controla apenas o tiro da Nariko
 */
void narikoShooting(Entity *nariko, Entity *fire, int limitX) 
{
    // Tiro de Fogo
    if (fire->pos.x < 0) { 
        if (rand() % 30 == 0) { // Chance de atirar
            fire->pos.x = nariko->pos.x - 2;
            fire->pos.y = nariko->pos.y; // Mesma linha da Nariko
            strcpy(fire->sprite[0], "🔥");
        }
    } else {
        // Limpa posição antiga
        printText("  ", fire->pos.x, fire->pos.y, WHITE, WHITE);
        
        fire->pos.x -= FIRE_SPEED;
        
        // Se bateu no limite esquerdo, reseta
        if (fire->pos.x <= limitX) {
            printText("  ", fire->pos.x, fire->pos.y, WHITE, WHITE); // Garante limpeza
            fire->pos.x = -10; 
        } else {
            // Desenha na nova posição
            printText("🔥", fire->pos.x, fire->pos.y, YELLOW, RED);
        }
    }
}