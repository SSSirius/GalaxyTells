
#pragma once
#include "ofMain.h"
#include "Params.hpp"
class star
{
public:
    ofVec3f pos;
    ofVec3f posback;
    ofVec3f siz;
    ofVec3f acc;
    float life;
    float maxLife;
    float vx, vy,vz,dre,alpha = 255;
    float ini_z,colr,colb,lifes;
    int num,size;
    star();
    virtual ~star(){};
    
    void resetForce();
    void setAttractPoints( vector <ofPoint> * attract );
    
    void addForce(float x, float y,float z);
    void addDampingForce();
    void distory();
    void setInitialCondition( float _ew, float _eh,int _num,int _size,float _dr,vector <float> _dis);
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
    vector <float> dis;
//    ofPixels pixels;
    
protected:
private:
    
};
//extern Params params;



