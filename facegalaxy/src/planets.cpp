#include "planets.hpp"
//#include "ofMain.h"
//#include "Params.hpp"
//------------------------------------------------------------
//Params param;
//Params param;

planet::planet(){
 
    
//    gui.setup();
//    gui.add(ini_z.setup("ini_Z",20,0,50));
//    gui.add(colr.setup("color_r",255,100,255));
//    gui.add(colb.setup("color_b",150,100,255));
//    gui.add(lifes.setup("lifespan",370,200,400));
//      setInitialCondition(0,0,0);
   
    iscons=false;
    
}
void planet::update(){
//    vel+=acc;
    pos+=vel;
//    acc*=0;
    
//    if(pos.z<-50 || pos.z>50){
//        vel.z*=-1;
////        vel.z=ofMap(pos)
//    }
    if(life<100){
       pos.z=pos.z * (1.-0.03);
        
    }
    posback.x=pos.x*2;
    posback.y=pos.y*2;
    posback.z=pos.z*-2;
//    vel.normalize();
//    vel*=0.1;
    
}
//------------------------------------------------------------
void planet::resetForce(){
    // we reset the forces every frame
//    frc.set(0,0,0);
}

//------------------------------------------------------------
void planet::setAttractPoints( vector <ofPoint> * attract ){
//    attractPoints = attract;
}
//------------------------------------------------------------
void planet::addForce(float x, float y,float z){
    // add in a force in X and Y for this frame.
//    frc.x = frc.x + x;
//    frc.y = frc.y + y;
//    frc.z = frc.z + z;
}

//------------------------------------------------------------
void planet::addDampingForce(){
    
//    frc.x = frc.x - vel.x * damping;
//    frc.y = frc.y - vel.y * damping;
//    frc.z = frc.z - vel.z * damping;
}

//------------------------------------------------------------
void planet::setInitialCondition( float _vx, float _vy, float _vz){
    //    pos.set(ofRandom(ofGetWidth()*0,ofGetWidth()),ofRandom(ofGetHeight(),ofGetHeight()),ofRandom(-ofGetHeight()*.5,ofGetHeight()*.5));
    pos.set(0,0,ofRandom(-ini_z,ini_z));
//    vel.set(_vx,_vy,_vz);
    vel.set(_vx,_vy,_vz);
//    ini_z=param.ini_z;
    colr=param.colh;
    colb=param.colb;
//    life=ofRandom(param.lifes-80,param.lifes);
    maxLife=life;
}

//------------------------------------------------------------

void planet::distory(){
    
    
}
//------------------------------------------------------------
void planet::draw(){
//     gui.draw();
    float gAndA = ofMap(life, 0, maxLife, 0, 255);
//    cout<< acc << endl;p
    ofPushStyle();
    ofColor fire  = ofColor
    (gAndA,ofMap(life, 0, maxLife, 100,colr), ofMap(life, 0, maxLife, colb, 0), gAndA);
//    ofColor smoke    = ofColor(34, 32, 30);
    
//    float lerp   = ofClamp(dist/maxdist, 0, 1);
//    color    = fire.lerp(smoke, lerp);
     float r = ofMap(gAndA, 255, 0, 1, 5);
//    material.setEmissiveColor( color );
//    material.begin();
        ofSetColor(fire);
     ofFill();
    //    if(dist< 100){
    //        ofSetColor(255,255,255);
    //        ofDrawLine(0,0,0,pos.x,pos.y,pos.z);
    //
    //    }
    life--;
    
    ofPushMatrix();
    ofTranslate(pos);
    ofDrawSphere(0,0,0, r);
//    ofDrawLine(0,0,0,5,5,5);
    num+=ofMap(alpha, 255, 0, 3, 0);
//    num++;
    alpha-=0.1;
    ofPopMatrix();
    ofPushMatrix();
    
    ofTranslate(posback);
    ofScale(-1,-1.3,0.5);
  
    ofColor fire2  = ofColor(gAndA,ofMap(life, 0, maxLife,100,colr*1.2), ofMap(life, 0, maxLife, colb*0.8, 100), gAndA*0.4);
//    float hue = ofMap(i, 0, nArrows, 127, 255);        // blue to red
//     ofColor fire2 = ofColor::fromHsb(hue, 255, 220);
//
    ofSetColor(fire2);
//      ofDrawSphere(0,0,0, r);
    //    ofDrawLine(0,0,0,5,5,5);
    num+=ofMap(alpha, 255, 0, 3, 0);
    //    num++;
    alpha-=0.1;
    ofPopMatrix();
//    material.end();
    
    ofPopStyle();
    
}

bool planet::boundary(){
    if(life <= 0) return true;
    return false;
}


