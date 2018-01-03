//
// Created by black on 12/20/17.
//

#include "areaOfEffect.h"

areaOfEffect::areaOfEffect() {

}

void areaOfEffect::show_area(int x, int y, square **tab) {

    if (x < 0 || x > 9) return;
    if (y < 0 || y > 9) return;
    if (tab[x][y].show == true) return;

    if (tab[x][y].value != 9 && tab[x][y].show == false)
        tab[x][y].show = true;

    if (tab[x][y].value != 0) return;

    areaOfEffect::show_area(x - 1, y - 1, tab);
    areaOfEffect::show_area(x - 1, y, tab);
    areaOfEffect::show_area(x - 1, y + 1, tab);
    areaOfEffect::show_area(x + 1, y - 1, tab);
    areaOfEffect::show_area(x + 1, y, tab);
    areaOfEffect::show_area(x + 1, y + 1, tab);
    areaOfEffect::show_area(x, y - 1, tab);
    areaOfEffect::show_area(x, y, tab);
    areaOfEffect::show_area(x, y + 1, tab);

}

areaOfEffect::~areaOfEffect() {


}