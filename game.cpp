//
// Created by sjal on 11/22/17.
//

#include "game.h"

WINDOW *game(int maxY, int changelingMaxX) {
    int startx,starty;
    int gameMaxY, gameMaxX;

    WINDOW *gameWindow = newwin(maxY - 1, 0, 0, changelingMaxX);
    box(gameWindow, 0, 0);
    wbkgd(gameWindow, COLOR_PAIR(1));

    getbegyx(gameWindow, starty,startx);
    getmaxyx(gameWindow, gameMaxY, gameMaxX);
    ++starty;
    ++startx;

    for (int i = 0; i < gameMaxY-2; ++i){
        move(starty+i,startx);
        for (int j = 0; j < gameMaxX-2; ++j){
            addch('.');
        }
    }

    wrefresh(gameWindow);
    return gameWindow;
}