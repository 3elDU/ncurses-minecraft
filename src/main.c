#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "world.h"
#include "colors.h"
#include "block.h"
#include "util.h"

int main(int argc, char *argv[]) {
    srand((unsigned)time(0));
    initscr();

    // exiting if terminal isn't supporting colors
    if (has_colors() == FALSE) {
        endwin();
        puts("Terminal doesn't support colors!");
        return 1;
    }
    start_color();
    init_custom_colors();

    set_escdelay(0);
    raw();
    halfdelay(0);
    keypad(stdscr, true);
    noecho();    
    timeout(0);
    curs_set(0);
    

    // creating the world
    struct World* world = initWorld(1024, 128);

    wclear(stdscr);

    bool running = true;

    int player_x = 0, player_y = 25;
    struct Block player = {.id=custom, .sybmol='Y', .color_pair=getColor(COLOR_BLUE, COLOR_BLACK), .bold=true, .dim=false};
    bool generateTail = false;
    
    long long lastPhysicsUpdate = 0;
    
    while (running) {
        
        // inputs
        int ch;
        while ((ch = getch()) != ERR) {
            if (ch == 'q' || ch == 'Q') running = false;
            else if (ch == 'w') {
                if (getBlock(world, player_x, player_y+10).canStepOn) player_y += 10;
            }
            else if (ch == 'a') {
                if (getBlock(world, player_x-1, player_y).canStepOn) player_x--;
                else if (getBlock(world, player_x-1, player_y+1).canStepOn) {
                    player_x--; player_y++;
                }
            }
            else if (ch == 's') {

            }
            else if (ch == 'd') {
                if (getBlock(world, player_x+1, player_y).canStepOn) player_x++;
                else if (getBlock(world, player_x+1, player_y+1).canStepOn) {
                    player_x++; player_y++;
                }
            }

            else if (ch == 'j') { // place block on the left
                if (getBlock(world, player_x-1, player_y).canStepOn) setBlock(world, player_x-1, player_y, initBlockById(ore));
            }
            else if (ch == 'J') { // break block on the left
                setBlock(world, player_x-1, player_y, initBlockById(air));
            }

            else if (ch == 'l') { // place block on the right
                if (getBlock(world, player_x+1, player_y).canStepOn) setBlock(world, player_x+1, player_y, initBlockById(ore));
            }
            else if (ch == 'L') { // break block on the right
                setBlock(world, player_x+1, player_y, initBlockById(air));
            }

            else if (ch == 't') generateTail = !generateTail;
        }
        
        for (int x = 0; x < getmaxx(stdscr); x++) {
            for (int y = 0; y < getmaxx(stdscr); y++) {
                
                int resX, resY;

                resX = player_x - getmaxx(stdscr)/2 + x;
                resY = player_y - getmaxy(stdscr)/2 + y;

                struct Block block = getBlock(world, resX, resY);

                renderBlock(stdscr, block, x, getmaxy(stdscr)-y);

            }
        }

        // player physics
        if (current_timestamp() - lastPhysicsUpdate >= 33) {
            if (getBlock(world, player_x, player_y-1).canStepOn) {
                player_y--;
            }

            lastPhysicsUpdate = current_timestamp();
        }

        if (generateTail) {
            struct Block playerTail = {.id=custom, .sybmol='$', .color_pair=getColor(COLOR_YELLOW, COLOR_BLACK), .bold=false, .dim=false, .canStepOn=true};
            setBlock(world, player_x, player_y, playerTail);
        }

        if ((getmaxx(stdscr)/2) % 2 == 1) {
            renderBlock(stdscr, player, getmaxx(stdscr)/2, getmaxy(stdscr)/2);
        }
        else {
            renderBlock(stdscr, player, getmaxx(stdscr)/2, getmaxy(stdscr)/2 + 1);
        }

        refresh();
    }

    getch();
    endwin();

    return 0;
}