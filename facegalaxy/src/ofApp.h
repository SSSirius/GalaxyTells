#pragma once

#include "ofMain.h"
//#include "ofxOsc.h"
#include "stars.hpp"
#include "Params.hpp"
#include "ofxGui.h"
#include "ofxFaceTracker2.h"
#include "ofxCv.h"
#include "Calc.hpp"
//#define HOST "149.31.200.42"

//#define PORT 8000
static std::vector<float> createGaussianWeights(int radius, float variance);
static float Gaussian(float x, float mean, float variance);

using namespace ofxCv;
using namespace cv;
class ofApp : public ofBaseApp{

	public:
		void setup();
    
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
  vector <planet> planets;
    vector<star> stars;
    vector<float> dis;
    
//    ofEasyCam cam;
    
    ofShader bloom;
    ofFbo fbo, onePassFbo, twoPassFbo;
    
    ofEasyCam cam;
    
  ofShader blurShader;
    int count=0;
    ofxPanel gui;
    ofxFaceTracker2 tracker;
    ofVideoGrabber grabber;
    ofxToggle showface,showdata,showrecord,ifdetect;
    ofxLabel datapanel;
    float ini_z,colb,colr,colg;
//    float colr;
    vector <float> mouths;
      vector <float> mouthups;
      vector <float> noses;
      vector <float> eyesizes;
      vector <float> eyedists;
      vector <float> faces;
    int record_index=0;
    vector <ofImage> records;
//    vector <float> mouths;
    
    vector<ofVec4f> track_data;
    float mouth,mouthup,nose,eyesize,eyedist,face;
    float ew,eh,degree;
    int size;
    int count_stable=0;
    bool is_faceshow =false;
    ofPixels pixels;
    Calc calculat;
//    float record_x = 300f;
//        float record_y = 200f;
    bool  bSnapshot = false;
//    float oripara_sum,nowpara_sum;
//   ofxOscReceiver receiver;
    ofImage btn_enter,btn_galaxy,btn_gallary,lab,face_btn;
    
//    vector<ofPoint> emotion_pos,relation_pos,luck_pos;
     vector <ofImage> img_records;
    ofPolyline emotion_line,relationship_line,luck_line;
};
//extern Params params;

