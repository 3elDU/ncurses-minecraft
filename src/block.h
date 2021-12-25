#ifndef BLOCK_H
#define BLOCK_H

#include <stdbool.h>
#include <ncurses.h>

enum BLOCK_ID {
    air,
    bedrock,
    stone,
    ore,
    dirt,
    grass,
    flower,
    water,

    custom,
};

struct Block {
    enum BLOCK_ID id;

    char sybmol;
    unsigned color_pair;
    bool bold;
    bool dim;
    
    bool canStepOn;

    int animationState;
};

struct Block initBlockById(enum BLOCK_ID);
struct Block initCustomBlock(enum BLOCK_ID id, char symbol, unsigned color_pair, bool bold, bool dim, bool canStepOn);

void renderBlock(WINDOW* window, struct Block block, unsigned x, unsigned y);

#endif