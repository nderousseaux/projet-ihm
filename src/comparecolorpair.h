#ifndef COMPARECOLORPAIR_H
#define COMPARECOLORPAIR_H

#include "colorpair.h"

class CompareColorPair
{
    public:
        //Constructeur
        CompareColorPair();

        //Surcharge ()
        bool operator() (ColorPair a, ColorPair b);
};

#endif // COMPARECOLORPAIR_H
