#ifndef COLORS_H
#define COLORS_H

#include <ncurses.h>

void init_custom_colors();
unsigned getColor(unsigned foreground, unsigned background);

void activateColor(unsigned clr);
void deactivateColor(unsigned clr);

#endif