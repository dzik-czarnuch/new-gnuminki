//
// Created by sjal on 11/22/17.
//
#include "status.h"

WINDOW *status(int maxY, int maxX) {
    WINDOW *statusWindow = newwin(maxY, maxX, 0, 0);
    box(statusWindow, 0, 0);
    wbkgd(statusWindow, COLOR_PAIR(1));

    mvwprintw(statusWindow, 0, (getmaxx(statusWindow) / 2) - 3, " Status "); //-2 'cause borders
    mvwprintw(statusWindow, 2, 2, "Flags\t: %d\t", 0, 0, maxY, maxX);

    wrefresh(statusWindow);
    return statusWindow;
}