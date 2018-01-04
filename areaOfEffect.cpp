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

    if (tab[x][y].value != 9 && !tab[x][y].show) {
        tab[x][y].show = true;
        switch (tab[x][y].value){
            case 0: {
                mvaddch(boardY,boardX,' ');
                break;
            }
            case 1: {
                mvaddch(boardY,boardX,'1');
                break;
            }
            case 2: {
                mvaddch(boardY,boardX,'2');
                break;
            }
            case 3: {
                mvaddch(boardY,boardX,'3');
                break;
            }
            case 4: {
                mvaddch(boardY,boardX,'4');
                break;
            }
            case 5: {
                mvaddch(boardY,boardX,'5');
                break;
            }
            case 6: {
                mvaddch(boardY,boardX,'6');
                break;
            }
            case 7: {
                mvaddch(boardY,boardX,'7');
                break;
            }
            case 8: {
                mvaddch(boardY,boardX,'8');
                break;
            }
            default:
                mvaddch(boardY,boardX,'X');
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