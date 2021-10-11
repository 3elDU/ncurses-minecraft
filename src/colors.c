#include "colors.h"
#include "util.h"

void init_custom_colors() {
    for (byte i = 0; i < 8; i++) {
        for (byte j = 0; j < 8; j++) {
            short resulting_id = i;
            resulting_id <<= 4;
            resulting_id += j;

            //printf("id %hu: fg %u bg %u\n", resulting_id, i, j);
            
            init_pair(resulting_id, i, j);
        }
    }
}

unsigned getColor(unsigned foreground, unsigned background) {
    short resulting_id = foreground;
    resulting_id <<= 4;
    resulting_id += background;
}

void activateColor(unsigned clr) {
    attron(clr);
}

void deactivateColor(unsigned clr) {
    attroff(clr);
}