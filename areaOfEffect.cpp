//
// Created by black on 12/20/17.
//

#include "areaOfEffect.h"

areaOfEffect::areaOfEffect() {

}

void areaOfEffect::show_area(int xsize, int ysize, int x, int y, int offset, square **tab) {

    int boardX = x + offset + 1;
    int boardY = y + 1;

    if (x < 0 || x > xsize) return;
    if (y < 0 || y > ysize) return;
    if (tab[x][y].show) return;

    if (tab[x][y].value != 9) {
        tab[x][y].show = true;
        switch (tab[x][y].value){
            case 0: {
                mvaddch(boardY,boardX,' ');
                break;
            }
            case 1: {
                attron(COLOR_PAIR(5));
                mvaddch(boardY,boardX,'1');
                attroff(COLOR_PAIR(5));
                break;
            }
            case 2: {
                attron(COLOR_PAIR(6));
                mvaddch(boardY,boardX,'2');
                attroff(COLOR_PAIR(6));
                break;
            }
            case 3: {
                attron(COLOR_PAIR(7));
                mvaddch(boardY,boardX,'3');
                attroff(COLOR_PAIR(7));
                break;
            }
            case 4: {
                attron(COLOR_PAIR(8));
                mvaddch(boardY,boardX,'4');
                attroff(COLOR_PAIR(8));
                break;
            }
            case 5: {
                attron(COLOR_PAIR(9));
                mvaddch(boardY,boardX,'5');
                attroff(COLOR_PAIR(9));
                break;
            }
            case 6: {
                attron(COLOR_PAIR(10));
                mvaddch(boardY,boardX,'6');
                attroff(COLOR_PAIR(10));
                break;
            }
            case 7: {
                attron(COLOR_PAIR(11));
                mvaddch(boardY,boardX,'7');
                attroff(COLOR_PAIR(11));
                break;
            }
            case 8: {
                attron(COLOR_PAIR(12));
                mvaddch(boardY,boardX,'8');
                attroff(COLOR_PAIR(12));
                break;
            }
            default:
                //do nothing
                break;
        }
    }

    if (tab[x][y].value != 0) return;

    areaOfEffect::show_area(xsize, ysize,x - 1, y - 1, offset, tab);
    areaOfEffect::show_area(xsize, ysize,x - 1, y, offset, tab);
    areaOfEffect::show_area(xsize, ysize,x - 1, y + 1, offset, tab);
    areaOfEffect::show_area(xsize, ysize,x + 1, y - 1, offset, tab);
    areaOfEffect::show_area(xsize, ysize,x + 1, y, offset, tab);
    areaOfEffect::show_area(xsize, ysize,x + 1, y + 1, offset, tab);
    areaOfEffect::show_area(xsize, ysize,x, y - 1, offset, tab);
    areaOfEffect::show_area(xsize, ysize,x, y, offset, tab);
    areaOfEffect::show_area(xsize, ysize,x, y + 1, offset,tab);

}

areaOfEffect::~areaOfEffect() {


}