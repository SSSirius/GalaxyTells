
#include "Calc.hpp"
//Params param;
void Calc::setup() {
    
    mouth=90;
    mouthver=10;
    nose=90;
    eyedist=80;
    eyesize=60;
    face=400;
}

void Calc::update(float _mouth,float _mouthver,float  _nose,float _eyedis,float  _eyesize,float _face) {
    
    mouth=_mouth;
    mouthver=_mouthver;
    nose=_nose;
    eyedist=_eyedis;
    eyesize=_eyesize;
    face=_face;
    facer=abs(face/400.*100);
    mouthr=abs(mouth/face*100);
    mouthupr=abs(mouthver/mouth*100);
    eyesizer=abs(eyesize/face*100);
    eyedistr=abs(eyedist/face*100);
    noser=abs(nose/face*100);
//    cout <<  nose * (1.-0.4) + ofMap(mouthr,30,50,0,255) * 0.4 << endl;

}

