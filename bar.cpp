//
// Created by sjal on 11/9/17.
//

#include "bar.h"

WINDOW *bar(int maxY) {
    int height = 1;

    WINDOW *statusBar = newwin(height, 0, maxY - height, 0);
    wbkgd(statusBar, COLOR_PAIR(2));

    waddstr(statusBar, " F2:New Game\t\tF12:Exit");

    wrefresh(statusBar);
    return statusBar;
}