//w
// Created by black on 12/20/17.
//

#include "plant.h"

plant::plant() {


}

bool plant::set_mine(int x, int y, int xsize, int ysize, square **tab) {

    int pos_x = x;
    int pos_y = y;

    if (tab[pos_x][pos_y].value != 9) {

        tab[pos_x][pos_y].value = 9; //set bomb

        for (int i = -1; i < 2; i++) {

            for (int j = -1; j < 2; j++) {
                if ((pos_x + j) < 0 || (pos_y + i) < -1) continue; //border
                if ((pos_x + j) > xsize-1 || (pos_y + i) > ysize+1) continue; //border

                if (tab[pos_x + j][pos_y + i].value == 9) continue; //mine
                tab[pos_x + j][pos_y + i].value += 1;
            }
        }
    }
    return true;
}

int plant::mine_plant(int xsize, int ysize, square **tab) {


    int pos_x, pos_y;
    int mine_number = (int)((xsize * ysize) * 0.1);

    srand(time(NULL));

    while (mine_number > 0) {

        pos_x = rand() % xsize;
        pos_y = rand() % ysize;

        if (tab[pos_x][pos_y].value != 9) {

            plant::set_mine(pos_x, pos_y, xsize, ysize, tab);
            mine_number--;
        }
    }
}

plant::~plant() {


}