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
    memset(result->world, 0, size_x * size_y * sizeof(struct Block));
    generateWorld(result);

    return result;
}

void generateWorld(struct World* world) {
    int cur_y = 20;
    
    for (int x = 0; x < world->size_x; x++) {
        for (int y = world->size_y-1; y >= 0; y--) {
            
            struct Block cur_block;

            if (y <= cur_y) {
                if (y == cur_y) cur_block = initBlockById(grass);
                else if (cur_y - y <= 3) cur_block = initBlockById(dirt);
                else if ( randomRange(0, 5) == 5 ) cur_block = initBlockById(ore);
                else if (y > 0) cur_block = initBlockById(stone);
                else if (y == 0) cur_block = initBlockById(bedrock);
            }
            else cur_block = initBlockById(air);

            setBlock(world, x, y, cur_block);
        }

        if (x % 2 == 0) cur_y += randomRange(-1, 1);
    }
}