//
// Created by black on 12/20/17.
//

#ifndef GNUMINKI_AREAOFEFFECT_H
#define GNUMINKI_AREAOFEFFECT_H

#include <ncurses.h>
#include "square.h"

class areaOfEffect : public square {
public:
    areaOfEffect();

    void show_area(int xsize, int ysize, int x, int y, int offset, square **tab); //odslanianie obszarow pustych
    ~areaOfEffect();
};


#endif //GNUMINKI_AREAOFEFFECT_H
