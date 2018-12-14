#pragma once
#include "ofMain.h"
//#include "planets.hpp"

class Calc {
public:
    void setup();
    void update(float _mouth,float _mouthver,float  _nose,float _eyedis,float  _eyesize,float _face);
//    ofPoint eCenter;    //Emitter center
    float mouth,mouthver,nose,eyedist,eyesize,face;
   float mouthr,mouthupr,noser,eyedistr,eyesizer,facer;
    int size;
};

//extern Params param; //Declaration of a global variable


