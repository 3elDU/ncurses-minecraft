#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "world.h"
#include "colors.h"
#include "block.h"
#include "util.h"
#include "player.h"
#include "log.h"

int main(int argc, char *argv[]) {
    // creating the logger object
    struct LogObject* log = createLog(13, "game_log.log");

    logPrintln(log, "hello, world!");
    logPrintln(log, "this is test!");

    srand((unsigned)time(0));
    initscr();

    // exiting if terminal isn't supporting colors
    if (!has_colors()) {
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
    struct World* world = initWorld(1024, 1024);

    wclear(stdscr);

    bool running = true;

    int player_x = 0, player_y = 120;
    struct Block player = {.id=custom, .sybmol='Y', .color_pair=getColor(COLOR_BLUE, COLOR_BLACK), .bold=true, .dim=false};
    bool generateTail = false;
    
    long long lastPhysicsUpdate = 0;
    
    clear();
    while (running) {
        long long frameStart = current_timestamp();
        
        // inputs
        int ch;
        while ((ch = getch()) != ERR) {
            if (ch == 'q' || ch == 'Q') running = false;
            /*
            else if (ch == 'w' || ch == 'W') {
                if (getBlock(world, player_x, player_y+1).canStepOn) player_y++;
            }
            */

            else if (ch == 'c' || ch == 'C') { // Generate new world

            }

            else if (ch == 'a' || ch == 'A') {
                if (getBlock(world, player_x-1, player_y).canStepOn) player_x--;
                else if (getBlock(world, player_x-1, player_y+1).canStepOn) {
                    player_x--;
                    player_y++;
                }
            }
            else if (ch == 's' || ch == 'S') {
                if (getBlock(world, player_x, player_y-1).canStepOn) player_y--;
            }
            else if (ch == 'd' || ch == 'D') {
                if (getBlock(world, player_x+1, player_y).canStepOn) player_x++;
                else if (getBlock(world, player_x+1, player_y+1).canStepOn) {
                    player_x++;
                    player_y++;
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

            else if (ch == 'i') { // place block on top
                if (getBlock(world, player_x, player_y+1).canStepOn) setBlock(world, player_x, player_y+1, initBlockById(ore));
            }
            else if (ch == 'I') { // break block on top
                setBlock(world, player_x, player_y+1, initBlockById(air));
            }

            else if (ch == ',') { // place block on bottom
                if (getBlock(world, player_x, player_y+1).canStepOn) {
                    setBlock(world, player_x, player_y, initBlockById(ore));
                    player_y++;
                }
            }
            else if (ch == '<') { // break block on bottom
                setBlock(world, player_x, player_y-1, initBlockById(air));
            }




            // diagonal

            else if (ch == 'm') { // place block on the bottom-left
                if (getBlock(world, player_x-1, player_y-1).canStepOn) setBlock(world, player_x-1, player_y-1, initBlockById(ore));
            }
            else if (ch == 'M') { // break block on the bottom-left
                setBlock(world, player_x-1, player_y-1, initBlockById(air));
            }

            else if (ch == '.') { // place block on the bottom-right
                if (getBlock(world, player_x+1, player_y-1).canStepOn) setBlock(world, player_x+1, player_y-1, initBlockById(ore));
            }
            else if (ch == '>') { // break block on the bottom-right
                setBlock(world, player_x+1, player_y-1, initBlockById(air));
            }


            else if (ch == 'u') { // place block on the top-left
                if (getBlock(world, player_x-1, player_y+1).canStepOn) setBlock(world, player_x-1, player_y+1, initBlockById(ore));
            }
            else if (ch == 'U') { // break block on the top-left
                setBlock(world, player_x-1, player_y+1, initBlockById(air));
            }

            else if (ch == 'o') { // place block on the top-right
                if (getBlock(world, player_x+1, player_y+1).canStepOn) setBlock(world, player_x+1, player_y+1, initBlockById(ore));
            }
            else if (ch == 'O') { // break block on the top-right
                setBlock(world, player_x+1, player_y+1, initBlockById(air));
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

        // physics
        if (current_timestamp() - lastPhysicsUpdate >= 33) {
            if (getBlock(world, player_x, player_y-1).canStepOn) player_y--;

            lastPhysicsUpdate = current_timestamp();
        }

        if (generateTail) {
            struct Block playerTail = {.id=custom, .sybmol='$', .color_pair=getColor(COLOR_YELLOW, COLOR_BLACK), .bold=false, .dim=false, .canStepOn=true};
            setBlock(world, player_x, player_y, playerTail);
        }

        renderBlock(stdscr, player, getmaxx(stdscr)/2, getmaxy(stdscr)/2 + getmaxy(stdscr)%2);

        refresh();

        long long frameEnd = current_timestamp();

        usleep(10000);
        /*
        long long toSleep = 16666 - (frameEnd - frameStart);
        if (toSleep > 0) {
            usleep(toSleep);
        }
        */
    }

    getch();
    endwin();

    return 0;
}