#include "comparecolorpair.h"

CompareColorPair::CompareColorPair(){}

bool CompareColorPair::operator() (ColorPair a, ColorPair b){
    if(a.getId() < b.getId()){
        return true;
    }
    else{
        return false;
    }
}
