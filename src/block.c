#include "block.h"
#include "colors.h"

struct Block initBlockById(enum BLOCK_ID id) {
    switch (id) {
        case air:
            return (struct Block) {air, ' ', getColor(COLOR_BLACK, COLOR_BLACK), false, true, true};

        case bedrock:
            return (struct Block) {bedrock, '#', getColor(COLOR_WHITE, COLOR_BLACK), true, true, false};

        case stone:
            return (struct Block) {stone, '0', getColor(COLOR_WHITE, COLOR_BLACK), false, true, false};

        case ore:
            return (struct Block) {ore, '$', getColor(COLOR_YELLOW, COLOR_BLACK), true, false, false};

        case dirt:
            return (struct Block) {dirt, '#', getColor(COLOR_YELLOW, COLOR_BLACK), false, true, false};

        case grass:
            return (struct Block) {grass, '_', getColor(COLOR_GREEN, COLOR_BLACK), false, false, true};

        case flower:
            return (struct Block) {flower, '.', getColor(COLOR_YELLOW, COLOR_BLACK), false, false, true};

        case water:
            return (struct Block) {water, '~', getColor(COLOR_BLUE, COLOR_BLACK), false, false, true};

        default:
            return (struct Block) {custom, '#', getColor(COLOR_RED, COLOR_BLACK), false, true, false};
    }
}

struct Block initCustomBlock(enum BLOCK_ID id, char symbol, unsigned color_pair, bool bold, bool dim, bool canStepOn) {
    return (struct Block){.id=id, .sybmol=symbol, .color_pair=color_pair, .bold=bold, .dim=dim, .canStepOn=can_change_color};
}

void renderBlock(WINDOW* window, struct Block block, unsigned x, unsigned y) {
    mvwaddch(window, y, x, block.sybmol | COLOR_PAIR(block.color_pair) | (block.bold ? A_BOLD : 0) | (block.dim ? A_DIM : 0));
}