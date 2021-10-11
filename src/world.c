#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "util.h"

unsigned translateCoords(struct World* world, unsigned x, unsigned y) {
    return world->size_x * y + x;
}

void setBlock(struct World* world, unsigned x, unsigned y, struct Block block) {
    if (x < world->size_x && y < world->size_y) {
        world->world[translateCoords(world, x, y)] = block;
    }
}

struct Block getBlock(struct World* world, unsigned x, unsigned y) {
    if (x < world->size_x && y < world->size_y) {
        return world->world[translateCoords(world, x, y)];
    }
    return initBlockById(custom);
}

struct World* initWorld(unsigned size_x, unsigned size_y) {
    struct World* result = (struct World*)malloc(sizeof(struct World));

    result->size_x = size_x;
    result->size_y = size_y;

    result->world = (struct Block*)malloc(size_x * size_y * sizeof(struct Block));
    generateWorld(result);

    return result;
}

void generateWorld(struct World* world) {
    for (unsigned x = 0; x < world->size_x; x++) {
        for (unsigned y = 0; y < world->size_y; y++) {

            unsigned choice = randomRange(0, 15);
            struct Block block = initBlockById(air);

            if (choice <= 3) {
                block = initBlockById(grass);
            }
            else if (choice == 4) {
                block = initBlockById(flower);
            }
            else if (choice == 5) {
                block = initBlockById(stone);
            }

            setBlock(world, x, y, block);

        }
    }
}