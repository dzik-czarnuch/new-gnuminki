//
// Created by black on 12/20/17.
//

#include "areaOfEffect.h"

areaOfEffect::areaOfEffect() {

}

void areaOfEffect::show_area(int xsize, int ysize, int x, int y, square **tab) {

    if (x < 0 || x > xsize) return;
    if (y < 0 || y > ysize) return;
    if (tab[x][y].show) return;

    if (tab[x][y].value != 9 && !tab[x][y].show)
        tab[x][y].show = true;

    if (tab[x][y].value != 0) return;

    areaOfEffect::show_area(xsize, ysize,x - 1, y - 1, tab);
    areaOfEffect::show_area(xsize, ysize,x - 1, y, tab);
    areaOfEffect::show_area(xsize, ysize,x - 1, y + 1, tab);
    areaOfEffect::show_area(xsize, ysize,x + 1, y - 1, tab);
    areaOfEffect::show_area(xsize, ysize,x + 1, y, tab);
    areaOfEffect::show_area(xsize, ysize,x + 1, y + 1, tab);
    areaOfEffect::show_area(xsize, ysize,x, y - 1, tab);
    areaOfEffect::show_area(xsize, ysize,x, y, tab);
    areaOfEffect::show_area(xsize, ysize,x, y + 1, tab);

}

areaOfEffect::~areaOfEffect() {


}