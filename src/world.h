#ifndef WORLD_H
#define WORLD_H

#include "block.h"

struct World {
    unsigned size_x, size_y;

    struct Block *world;
};

unsigned translateCoords(struct World* world, unsigned x, unsigned y);

void setBlock(struct World* world, unsigned x, unsigned y, struct Block block);
struct Block getBlock(struct World* world, unsigned x, unsigned y);

void generateWorld(struct World* world);
struct World* initWorld(unsigned size_x, unsigned size_y);

#endif