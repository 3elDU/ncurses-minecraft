#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "util.h"
#include "perlin.h"

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
    /*
    for (unsigned x = 0; x < world->size_x; x++) {
        for (unsigned y = 0; y < world->size_y; y++) {

            float choice = perlin2d(x / 3.f, y / 3.f, 0.1, 16) * 2;
            struct Block block = initBlockById(air);

            if (choice <= 1) block = initBlockById(water);
            else if (choice <= 2) block= initBlockById(grass);
            else block = initBlockById(flower);

            setBlock(world, x, y, block);

        }
    }
    */

    int height = 80;
    int flatWidth = 2;

    for (int x = 0; x < world->size_x; x++) {
        for (int y = 0; y < world->size_y; y++) {

            struct Block block = initBlockById(air);

            if (y == height) block = initBlockById(grass);
            else if (y < height && y >= height-3) block = initBlockById(dirt);
            else if (y > 0 && y < height-3) block = initBlockById(stone);
            else if (y == 0) block = initBlockById(bedrock);

            setBlock(world, x, y, block);

        }

        if (x % flatWidth == 0) {
            height += randomRange(-1, 1);
            flatWidth = randomRange(1, 5);
        }
    }
}