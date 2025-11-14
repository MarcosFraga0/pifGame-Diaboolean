/**
 * @file entity.c
 * @date Nov, 9th 2025
 * @author Iza Malafaia
 * @details Implement entity features
 */

#include <stdio.h>
#include <string.h>

#include "entities/entity.h"

/**
 * @brief reset entity attributes
 * @param {Entity *entity} entity that will be redefined
 * @param {Vector2D initial} initial position of entity in room
 */
void resetEntity(Entity *entity, Vector2D initial)
{
    entity->pos.x = initial.x;
    entity->pos.y = initial.y;
    entity->vel.x = 0;
    entity->vel.y = 0;
    entity->collision.isColliding = 0;
    entity->collision.collisionType = collisionNone;
}

/**
 * @brief Atualiza velocidade de uma entidade
 * @param {Entity *entity} ponteiro de entidade
 * @param {Vector2D vel} velocidade
 */
void setEntityVel(Entity *entity, Vector2D vel)
{
    entity->vel.x = vel.x;
    entity->vel.y = vel.y;
}

/**
 * @brief Atualiza posição da entidade com base na velocidade
 * @param {Entity *entity} ponteiro de entidade
 */
void entityMove(Entity *entity)
{
    // entity is collision
    if (entity->collision.isColliding)
    {
        switch (entity->collision.collisionType)
        {
        case bearer:
            // continue stop
            entity->vel.x = 0;
            entity->vel.y = 0;
            break;
        default:
            break;
        }
    }

    entity->pos.x += entity->vel.x;
    entity->pos.y += entity->vel.y;
}

/**
 * @brief Limpa, atualia a posição do entity e mostra-o na tela
 * @param {Entity *entity} ponteiro de entidade
 */
void showEntity(Entity *entity)
{
    // clear drawn sprite
    for (int y = 0; y < entity->len.y; y++)
    {
        for (int x = 0; x < entity->len.x; x++)
        {
            // limpa pixel por pixel
            screenGotoxy(entity->pos.x + x, entity->pos.y + y);
            printf(" ");
        }
    }

    // apply velocity
    entityMove(entity);
    // draw sprite
    screenSetColor(entity->fg, entity->bg);
    for (int y = 0; y < entity->len.y; y++)
    {
        screenGotoxy(entity->pos.x, entity->pos.y + y);

        // if sprite have only one sprite layer
        if (entity->sprite[y][0] == '\0')
        {
            printf("%s", entity->sprite[0]);
        }

        int spriteLen = strlen(entity->sprite[y]);
        // if spritelen is smaller than entity len x, alto fill
        if (spriteLen > 0 && spriteLen < entity->len.x)
        {
            for (int x = 0; x < (entity->len.x / spriteLen) - 1; x++)
            {
                printf("%s", entity->sprite[y]);
            }
        }

        // if sprite have many sprite layers
        printf("%s", entity->sprite[y]);
    }
    screenSetNormal();

    entity->vel.x = 0;
    entity->vel.y = 0;
}

/**
 * @brief  mostra entity na tela
 * @param {Entity *entity} ponteiro de entidade
 */
void showEntityNoMove(Entity *entity)
{
    // clear drawn sprite
    for (int y = 0; y < entity->len.y; y++)
    {
        for (int x = 0; x < entity->len.x; x++)
        {
            // limpa pixel por pixel
            screenGotoxy(entity->pos.x + x, entity->pos.y + y);
            printf(" ");
        }
    }

    // draw sprite
    screenSetColor(entity->fg, entity->bg);
    for (int y = 0; y < entity->len.y; y++)
    {
        screenGotoxy(entity->pos.x, entity->pos.y + y);

        // if sprite have only one sprite layer
        if (entity->sprite[y][0] == '\0')
        {
            printf("%s", entity->sprite[0]);
        }

        int spriteLen = strlen(entity->sprite[y]);
        // if spritelen is smaller than entity len x, alto fill
        if (spriteLen > 0 && spriteLen < entity->len.x)
        {
            for (int x = 0; x < (entity->len.x / spriteLen) - 1; x++)
            {
                printf("%s", entity->sprite[y]);
            }
        }

        // if sprite have many sprite layers
        printf("%s", entity->sprite[y]);
    }
    screenSetNormal();
}

/**
 * @brief Limpa, atualiza a posição do entity (sem vel = 0) e mostra-o na tela
 * @param {Entity *entity} ponteiro de entidade
 */
void showEntityNoStop(Entity *entity)
{
    // clear drawn sprite
    for (int y = 0; y < entity->len.y; y++)
    {
        for (int x = 0; x < entity->len.x; x++)
        {
            // limpa pixel por pixel
            screenGotoxy(entity->pos.x + x, entity->pos.y + y);
            printf(" ");
        }
    }

    // apply velocity
    entity->pos.x += entity->vel.x;
    entity->pos.y += entity->vel.y;
    // draw sprite
    screenSetColor(entity->fg, entity->bg);
    for (int y = 0; y < entity->len.y; y++)
    {
        screenGotoxy(entity->pos.x, entity->pos.y + y);

        // if sprite have only one sprite layer
        if (entity->sprite[y][0] == '\0')
        {
            printf("%s", entity->sprite[0]);
        }

        int spriteLen = strlen(entity->sprite[y]);
        // if spritelen is smaller than entity len x, alto fill
        if (spriteLen > 0 && spriteLen < entity->len.x)
        {
            for (int x = 0; x < (entity->len.x / spriteLen) - 1; x++)
            {
                printf("%s", entity->sprite[y]);
            }
        }

        // if sprite have many sprite layers
        printf("%s", entity->sprite[y]);
    }
    screenSetNormal();
}

/**
 * @brief utiliza showEntity() para varias entidades
 * @param {Entity *entities} ponteiro de entidades
 */
void showEntities(EntityArray *entities)
{
    for (int i = 0; i < entities->len; i++)
    {
        showEntity(&entities->entities[i]);
    }
}

/**
 * @brief Check Collision between main entity and others entities
 * @param {Entity *entity} Entity for comparation
 * @param {Entity *entities} entities array
 * @param {int entitiesLen} tamanho do array de entidades
 */
void checkCollision(Entity *entity, EntityArray *entities)
{
    // indexs entities and entities
    int isCollision = 0;
    CollisionType collisionType = collisionNone;

    // get current position entity
    Vector2D pos = {entity->pos.x, entity->pos.y};
    // get next position (current pos + velocity)
    Vector2D entity_next_pos = {entity->vel.x + pos.x, entity->vel.y + pos.y};

    // get entity area (next pos + entity length)
    Vector2D entity_area = {
        entity_next_pos.x + entity->len.x,
        entity_next_pos.y + entity->len.y};

    for (int i = 0; i < entities->len; i++)
    {
        Entity *other_entity = &entities->entities[i];
        // get current entity position
        Vector2D other_entity_pos = {other_entity->pos.x, other_entity->pos.y};
        // get current entity area (current pos + len)
        Vector2D other_entity_area = {
            other_entity->pos.x + other_entity->len.x,
            other_entity->pos.y + other_entity->len.y};

        // if not is collision, continue
        /**
         * @brief check collision AABB
         */
        if (!(entity_next_pos.x < other_entity_area.x && // lado esquerdo da entidade à esquerda do lado direito da outra entitade
              entity_area.x > other_entity_pos.x &&      // lado direito da entidade à direita do lado esquerdo da outra entitade
              entity_next_pos.y < other_entity_area.y && // topo da entidade acima da parte inferior da outra entidade
              entity_area.y > other_entity_pos.y         // parte inferior da entidade abaixo do topo da outra entidade
              ))
        {
            other_entity->collision.isColliding = 0;
            continue;
        }

        // if collision, att true
        isCollision = 1;
        collisionType = other_entity->collision.collisionType;
        other_entity->collision.isColliding = 1;
    }

    // att values to entity
    entity->collision.isColliding = isCollision;
    entity->collision.collisionType = collisionType;
}