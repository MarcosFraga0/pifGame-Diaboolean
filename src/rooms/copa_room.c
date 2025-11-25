/**
 * @file copa_room.c
 * @details Sala da Copa
 */

#include <stdio.h>
#include "rooms/copa_room.h"
#include "screen.h"
#include "handlers/keyboardHandler.h"
#include "handlers/timeHandler.h"
#include "ui/dialog_box.h"
#include "ui/menu.h"
#include "animations/player.h"

// Define o tamanho da nossa "Salinha" dentro da tela grande
// A tela tem ~80x24. Faz uma sala de 40x14 no meio.
#define ROOM_X (MAXX / 2 - 20) // Começa no X 20
#define ROOM_Y (MAXY / 2 - 6)  // Começa no Y 6
#define ROOM_W 40              // Largura
#define ROOM_H 14              // Altura

void initCopaRoom(Entity *player, int *playerLife)
{
    // 1. Configuração Inicial do Jogador
    // Posiciona o player na porta (canto inferior direito da sala)
    player->pos.x = ROOM_X + 4;
    player->pos.y = ROOM_Y + ROOM_H - 2;
    player->collision.isColliding = 0;

    // 2. Define os Elementos
    Entity roomEntities[] = {
        
        // --- PAREDES (Para fechar a sala e deixá-la menor) ---
        // Parede Cima
        //{{posX, posY}, {velX, velY}, {lenX, leny}, {isColliding = 0, CollisionType = bearer}, char sprite[], screenColor fg, screenColor bg},
        {{ROOM_X, ROOM_Y}, {0,0}, {ROOM_W, 1}, {0, bearer}, {"-"}, WHITE, BROWN},
        // Parede Baixo
        {{ROOM_X, ROOM_Y + ROOM_H}, {0,0}, {ROOM_W, 1}, {0, bearer}, {"-"}, WHITE, BROWN},
        // Parede Esquerda
        {{ROOM_X, ROOM_Y}, {0,0}, {1, ROOM_H + 1}, {0, bearer}, {"⼁"}, WHITE, BROWN},
        // Parede Direita
        {{ROOM_X + ROOM_W, ROOM_Y}, {0,0}, {1, ROOM_H + 1}, {0, bearer}, {"⼁"}, WHITE, BROWN},

        // --- PORTA (Na parede de baixo, direita) ---
        {{ROOM_X + ROOM_W, ROOM_Y + ROOM_H - 2},
         {0, 0},
         {2, 1},
         {0, bearer},
         {"🚪"},
         WHITE, WHITE},

        // --- NPC: Tia da Cantina (Dentro do balcão) ---
        {{ROOM_X + ROOM_W - 16, ROOM_Y + 3},
         {0, 0}, {1, 1}, {0, bearer},
         {"👵"}, WHITE, WHITE},

        // --- O BALCÃO ---
        // Parte da Frente (Horizontal) - Protege a Tia
        {{ROOM_X + ROOM_W - 20, ROOM_Y + 5}, 
         {0, 0}, {16, 1}, {0, bearer},
         {"="}, WHITE, LIGHTGRAY},

        // Parte Lateral (Vertical) - Fecha o lado direito da Tia
        {{ROOM_X + ROOM_W - 20, ROOM_Y + 1}, 
         {0, 0}, {2, 5}, {0, bearer},
         {"⼁"}, WHITE, LIGHTGRAY},
         
        // --- NPC: Bombeiro (Sentado numa mesa?) ---
        {{ROOM_X + ROOM_W - 12, ROOM_Y + 6},
         {0, 0}, {1, 1}, {0, bearer},
         {"👨‍🚒"}, WHITE, WHITE},

        // --- MESAS (Para preencher o espaço vazio) ---
        // Mesa 1 (Perto do Bombeiro)
        {{ROOM_X + 4, ROOM_Y + 2}, 
         {0, 0}, {4, 2}, {0, bearer},
         {" "}, WHITE, BROWN}, // M de Mesa
         {{ROOM_X + 4, ROOM_Y + 4}, 
         {0, 0}, {4, 1}, {0, collisionNone},
         {"ˈ  ˈ"}, LIGHTGRAY, WHITE}, // M de Mesa
         
        // Mesa 2 (Mais abaixo)
        {{ROOM_X + 12, ROOM_Y + 2}, 
         {0, 0}, {4, 2}, {0, bearer},
         {" "}, WHITE, BROWN}, // M de Mesa
         {{ROOM_X + 12, ROOM_Y + 4}, 
         {0, 0}, {4, 1}, {0, collisionNone},
         {"ˈ  ˈ"}, LIGHTGRAY, WHITE}, // M de Mesa

        // --- PLACA ---
        {{ROOM_X + ROOM_W / 2, ROOM_Y - 2}, // Acima da parede
         {0, 0}, {4, 1}, {0, collisionNone},
         {"COPA"}, WHITE, WHITE},

         // cafe no balcão
        {{ROOM_X + ROOM_W - 8, ROOM_Y + 3}, 
         {0, 0}, {1, 1}, {0, trigger},
         {"☕"}, WHITE, WHITE},
    };

    int len = sizeof(roomEntities) / sizeof(roomEntities[0]);
    EntityArray entities = {len, roomEntities};

    Entity *coffee = &roomEntities[len - 1];
    Entity *porta = &roomEntities[4]; // Ajusta o índice se mudar a ordem (4 é a porta)
    Entity *tiaDoCoffee = &roomEntities[5];
    Entity *bombeiro = &roomEntities[8]; 

    // 3. Renderização
    screenInit(1); 
    showEntities(&entities);
    showEntity(player);
    screenUpdate();

    showDialogBox(player->sprite[0], "Voce", "Que fome... cheguei na copa.");

    char ch = 0;
    while (1)
    {
        if (keyhit())
        {
            ch = readch();
            setEntityVel(player, keyboardVelHandler(ch, 2));
            checkCollision(player, &entities);
        }

        if (timerTimeOver())
        {
            showMenu(&ch);
            showEntities(&entities);
            showEntity(player);
            screenUpdate();

            // Interação Bombeiro
            if (bombeiro->collision.isColliding)
            {
                bombeiro->collision.isColliding = 0;
                showDialogBox("👨‍🚒", "Bombeiro", "Assim tu me quebra! Cuidado com a mesa.");
            }

            // Interação Tia do cafe
            if (tiaDoCoffee->collision.isColliding){
                tiaDoCoffee->collision.isColliding = 0;
                showDialogBox(tiaDoCoffee->sprite[0], "Tia do Cafe", "O cafe ta quentinho!");
            }

            // Interação Porta
            if (porta->collision.isColliding)
            {
                showDialogBox(player->sprite[0], "Voce", "Barriga cheia... hora da aula!");
                break;
            }

            // Interação cafe
            if (coffee->collision.isColliding){
                *playerLife += 1;
                playerAddLife(player);
                coffee->len.y = 0;
                coffee->collision.isColliding = 0;
            }
        }
    }
}