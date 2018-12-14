#pragma once
//#include "ofMain.h"
#include "Params.hpp"
//#include "ofApp.h"
//#include "ofxGui.h"
class planet
{
public:
    ofVec3f pos;
    ofVec3f posback;
    ofVec3f vel;
    ofVec3f acc;
    float life;
    float maxLife;
    float vx, vy,vz, num, alpha = 255;
    float ini_z,colr,colb,lifes;
    planet();
    virtual ~planet(){};
    
    void resetForce();
    void setAttractPoints( vector <ofPoint> * attract );
    
    void addForce(float x, float y,float z);
    void addDampingForce();
    void distory();
    void setInitialCondition( float _vx, float _vy, float _vz);
    bool boundary();
    void update();
    void draw();
    float drag;
    float uniqueVal;
    float scale;
    float radius;
    float damping;
    float maxdist;
    float dist;
    bool iscons;
    ofColor color;
    vector <ofPoint> * attractPoints;
    ofMaterial material;
protected:
private:
    
};
//extern Params params;


