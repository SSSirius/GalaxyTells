#pragma once
#include "ofMain.h"
#include "planets.hpp"

class Params {
public:
    void setup();
    ofPoint eCenter;    //Emitter center
    float ini_z,dens,speed,dis;
   float colh,cols,colb;
    float zdiff,xydiff; //Friction, in the range [0, 1]
    float ew,eh,degree;
    int size;
};

extern Params param; //Declaration of a global variable

