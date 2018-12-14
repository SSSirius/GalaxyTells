
#include "stars.hpp"
//#include "ofMain.h"
//#include "Params.hpp"
//------------------------------------------------------------

star:: star(){
    
    pos.set(0,0,0);// add in a force in X and Y for this frame.
    
    iscons=false;
    //     for( int i=0; i<50; i++){
    //         dis.push_back(ofRandom(i));
    //     }
    radius=0.1;
}
void  star::update(){
//        vel+=acc;
    
}
//------------------------------------------------------------
void  star::resetForce(){
    // we reset the forces every frame
    //    frc.set(0,0,0);
}

//------------------------------------------------------------
void  star::setAttractPoints( vector <ofPoint> * attract ){
    //    attractPoints = attract;
}
//------------------------------------------------------------
void  star::addForce(float x, float y,float z){
    
}

//------------------------------------------------------------
void  star::addDampingForce(){
    
    //    frc.x = frc.x - vel.x * damping;
    //    frc.y = frc.y - vel.y * damping;
    //    frc.z = frc.z - vel.z * damping;
}

//------------------------------------------------------------
void  star::setInitialCondition( float _ew, float _eh,int _num,int _size,float _dre,vector <float> _dis){
    siz.x= _ew;
    siz.y= _eh;
    num=_num;
    dre=_dre;
    size=_size;
    dis=_dis;
}

//------------------------------------------------------------

void  star::distory(){
    
    
}
//------------------------------------------------------------
void  star::draw(){
    //     gui.draw();
        float gAndA = ofMap(num,0,size,  255,0);
//    ofRotateZ(-ofGetElapsedTimef()*0.05);
    ofPushMatrix();
    ofRotate(num*dre);
    //    ofNoFill();
    
    ofPushStyle();
    ofFill();
    
//    float color_range = ofMap(num,0,size, param.colr,50);
//    (this.thisindex) * colorrange * (random(0.8)) + (this.x / 900) * (colorrange + 0.2), random(0.9), sin(j * PI) - (this.thisindex)
    
    ofColor starcol2  = ofColor::fromHsb(ofMap(num,0,size,param.colh , param.colh*1.5), ofMap(num,0,size, param.cols*0.7,250),ofMap(num, 0, size, param.colb*1.2, 255),ofMap(param.colh,10,270, 0,255));
//    (ofMap(num,0,size, 120, param.colg),ofMap(num, 0, size,100,param.colr), ofMap(num, 0, size, param.colb, 0), ofMap(num,0,size, 255, 200));
//    ofColor starcol  = ofColor
    
    
    
//    (ofMap(num,0,size, param.colr,50),ofMap(num,0,size,  param.colr + 40,150), ofMap(num,0,size, 100,param.colb), ofMap(num,0,size, 255,240));
//    (ofMap(num,0,size, param.colr,50),ofMap(num,0,size, param.colg,150), ofMap(num,0,size, 100,param.colb), ofMap(num,0,size, 255,240));
    
//
    if (num< size*0.7){
    for( int i=0; i<param.dens/2; i++){
        ofVec3f starpos;
        starpos.z=-dis[i]* cos(ofMap(num,0.1,size,0,1.5707))*0.3;
        //       starpos.x = cos(i*15) * ofMap(i,0,50,0,siz.x);
        //       starpos.y = sin(i*15) * ofMap(i,0,50,0,siz.x);
        starpos.x = cos(dis[i]*PI)* sin(ofMap(i,0,20,0,siz.y))*siz.y*2;
        starpos.y = sin(dis[i]*PI)* sin(ofMap(i,0,20,0,siz.x))*siz.x*2;
        dist=starpos.length();
        maxdist=sqrt(siz.x*siz.x*4+siz.y*siz.y*4+ starpos.z* starpos.z);
        radius= ofMap(dist,0,maxdist,0.01,1);

         ofSetColor(starcol2);
         ofDrawSphere(starpos,radius);
//
    }}
    for( int i=0; i<param.dens; i++){
        ofVec3f starpos;
//        starpos.z=dis[i]*ofMap(num,0,size,0.2,0.04);
            starpos.z=dis[i]* cos(ofMap(num,0.1,size,0,1.5707))*0.3;
        starpos.x = cos(dis[i]*PI)* sin(ofMap(i,0,20,0,siz.y))*siz.y*ofMap(num,0,size,1,1.5);
        starpos.y = sin(dis[i]*PI)* sin(ofMap(i,0,20,0,siz.x))*siz.x*ofMap(num,0,size,1,1.5);
        dist=starpos.length();
        maxdist=sqrt(siz.x*siz.x+siz.y*siz.y+ starpos.z* starpos.z);
 
        
        float dis_mult = ofMap(dist,0,maxdist,0,param.colh);
        radius= ofMap(dist,0,maxdist,0.02,2)* ofMap(num,0,size,1,0.5);
        float hue = ofMap(num,0,size,param.colb, 255);        // blue to red
        ofColor starcol  =ofColor::fromHsb(ofMap(dist,0,maxdist,param.colh * 0.3 + dis_mult , param.colh*1.2 + dis_mult ), ofMap(dist,0,size, param.cols,255),ofMap(num, 0, size, param.colb, 255),ofMap(param.colh,-60,270, 0,255));
        
//        ofMap(dist,0,maxdist, 255,50)
//             ofColor starcol  =ofColor::fromHsb(255,255,255);
//        ofColor::fromHsb(hue,ofMap(num,0,size,120, param.colh), ofMap(dist,0,maxdist,150,255));
        ofSetColor(starcol);
        ofDrawSphere(starpos,radius);
//
    }
//
    ofPopStyle();
    ofPopMatrix();
    
}

bool  star::boundary(){
    if(life <= 0) return true;
    return false;
}



