#include "ofApp.h"
#include<vector>
//#include "iostream.h"
//#include "Params.hpp"
//--------------------------------------------------------------
//Params param;
//Params param;
void ofApp::setup(){
//      ofSetVerticalSync(true);
        bloom.load("shader/bloom.vert", "shader/bloom.frag");
//    oripara_sum=0;
//    nowpara_sum=0;
    record_index =0;
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA16F);
    onePassFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA16F);
    twoPassFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA16F);
//    testFbo.allocate(ofGetWidth()/2, ofGetHeight()/2, GL_RGBA, 1);
    grabber.setup(1280,720);
    param.setup();
    // Setup tracker
    tracker.setup();
    ofSetFrameRate(15);
    ofBackground(0);
    ofSetCircleResolution(200);
    for( int i=0; i<200; i++){
        dis.push_back(ofRandom(200-i));
//        cout <<ofRandom(1) <<endl;
    }
    gui.setup();
    gui.add(showface.setup("Face", false));
    gui.add(showdata.setup("Data", false));
    gui.add(showrecord.setup("Histroy", false));
    gui.add(ifdetect.setup("Predict", true));


    std::vector<float> coefficients;
    coefficients.clear();
    coefficients = createGaussianWeights(12, 0.2f);
    blurShader.load("shader/PassThru.vert", "shader/Blur.frag");
    blurShader.begin();
    blurShader.setUniform1i("blurRes", 12);
    blurShader.setUniform1f("sampleStep", 1.0);
    blurShader.setUniform1fv("coefficients", coefficients.data(), coefficients.size());
    blurShader.setUniform1i("preShrink", 2);
    blurShader.end();
    
    btn_galaxy.load("Buttons/On_Galaxy.png");
    btn_gallary.load("Buttons/On_Gallary.png");
    lab.load("Buttons/Analysis.png");
    face_btn.load("Buttons/ButtonFace.png");
}


//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    mouth=0;
    mouthup=0;
    nose=0;
    eyesize=0;
    eyedist=0;
    face=0;
  
    if(grabber.isFrameNew()){
        tracker.update(grabber);
    }
    mouths = tracker.mouthdist();
    mouthups = tracker.mouthvertidist();
    noses = tracker.nosedist();
    eyesizes = tracker.eyesize();
    eyedists = tracker.eyedist();
    faces= tracker.facedist();

    int i = 0;
    for(int i = 0; i < mouths.size(); i++){
       mouth+=mouths[i]/mouths.size();;
        mouthup+=mouthups[i]/mouths.size();;
        nose+= noses[i]/mouths.size();;
        eyesize+= eyesizes[i]/mouths.size();;
        eyedist+= eyedists[i]/mouths.size();;
        face+= faces[i]/mouths.size();;
    }
    calculat.update(mouth, mouthup, nose, eyedist, eyesize, face);
    

    float pct=0.1;
    
    if(ofToString(param.colh)=="nan"){
//
    param.colh= 0;
    param.cols=0;
    param.colb = 0;
    param.degree= 0;
    param.size=0;
    param.dens=0;
    }else{
//        oripara_sum =nowpara_sum;
//        colr =param.colh;
            param.colh =param.colh * (1.-pct) + ofMap(calculat.mouthr,35,53,0,255) * pct;
            param.cols = param.cols * (1.-pct) + ofMap(calculat.eyedistr,25,33,150,255)*pct;//
            param.colb = param.colb * (1.-pct) + ofMap(calculat.noser,34,43,180,255) * pct;
            param.degree= param.degree * (1.- pct)+ ofMap(calculat.mouthupr,30,150,9,25)* pct;
            param.size=param.size* (1.-pct) +ofMap(calculat.noser,34,43,30,70)* pct;
            param.dens=param.dens* (1.-pct)+ofMap(calculat.facer,50,100,20,200)* pct;
//         param.dens=param.dens* (1.-pct)+ofMap(calculat.mouthr,35,43,20,200)* pct;
//
    }
//
//    oripara_sum = param.colh +param.cols+param.colb+ param.degree+param.size+param.dens;
//    nowpara_sum = param.colh +param.cols+param.colb+ param.degree+param.size+param.dens;
}

//--------------------------------------------------------------
void ofApp::draw(){
  
    
    if(ifdetect){
    fbo.begin();
    
    ofClear(0, 0, 0, 0);
    ofPushMatrix;
    ofTranslate(ofGetWidth(),0);
    cam.begin();
    
    
    for(int i = 0; i < param.size; i++){
        star newstar;
        newstar.setInitialCondition(i*param.ew,i*param.eh,i,param.size,param.degree,dis);
        stars.push_back(newstar);
        
    }
    
    for(int i = 0; i < stars.size(); i++){
        stars[i].draw();
        
    }
    
    cam.end();
    ofPopMatrix;
    fbo.end();

    stars.clear();
    
    
    onePassFbo.begin();
    ofClear(0);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    blurShader.begin();
    
    blurShader.setUniform1i("isHorizontal", 0);
    fbo.draw(0, 0);
//    fbo.readToPixels(pixels);
//    img.setFromPixels(pixels);
    blurShader.end();
    
    onePassFbo.end();
    //
    // Y方向のガウシアンブラー
    twoPassFbo.begin();
    ofClear(0);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    blurShader.begin();
    blurShader.setUniform1i("isHorizontal", 1);
    
    onePassFbo.draw(0, 0);
    
    blurShader.end();
    
    twoPassFbo.end();
    
 
    
    //     ガウシアンブラーと元の描画内容を加算合成z
    bloom.begin();
    bloom.setUniformTexture("tex", fbo.getTexture(), 0.2);
    bloom.setUniformTexture("blur", twoPassFbo.getTexture(), 1);
    
    fbo.draw(0, 0);
    
    bloom.end();
       
    if(is_faceshow) tracker.drawMesh();
    if (bSnapshot){
            string fileName ;
//        img.clear();
         ofImage img;
        img.grabScreen(400,25,900,900);
        fileName = "snapshot_" + ofToString(record_index)+ ".png";
         img.save(fileName);
        record_index ++;
        ofImage tempimg(fileName);
        records.push_back(img);
        bSnapshot = false;
    }
//
    }
//    gui.draw();
    
//    if(showdata){
//        ofDrawBitmapString("nose:"+ofToString(calculat.noser),10,90);
//        ofDrawBitmapString("eyedist:"+ofToString(calculat.eyedistr),10,120);
//        ofDrawBitmapString("mouthwidth:"+ofToString( calculat.mouthr),10,150);
//        ofDrawBitmapString("mouthup:"+ofToString(calculat.mouthupr),10,180);
//        ofDrawBitmapString("face:"+ofToString(calculat.facer),10,210);
//        ofDrawBitmapString("eyelengh:"+ofToString(calculat.eyesizer),10,240);
//        ofDrawBitmapString("color_H:"+ofToString(param.colh),10,270);
//        ofDrawBitmapString("Color_S:"+ofToString(param.cols),10,300);
//        ofDrawBitmapString("color_B:"+ofToString( param.colb),10,330);
//        ofDrawBitmapString("convergence:"+ofToString(param.degree),10,360);
//        ofDrawBitmapString("scale:"+ofToString( param.size),10,390);
//        ofDrawBitmapString("density:"+ofToString( param.dens),10,410);
////        ofDrawBitmapString("different:"+ofToString(abs(oripara_sum-nowpara_sum)),10,440);
//    }
//count++;
    ofPushMatrix;
//    ofTranslate(ofGetWidth(),0);
//    ofScale(-1,1,1);
  
    ofPopMatrix;
    if(showrecord){
        ofFill();
        ofSetColor(0,0,0,100);
        ofRect(200,0,1500,1500);
        ofSetColor(255);
        for (int i= 0;i < records.size();i++) {
             records[i].draw(floorf(i%7)*180+200,floorf(i/7*200)+200,150,150);
            ofNoFill();
            ofRect(floorf(i%7)*180+200 ,floorf(i/7*200)+200 ,150,150);
            ofDrawBitmapString("Dec."+ofToString(i+1),floorf(i%7)*180+260,floorf(i/7*200)+370 );

        }
        
        ofSetColor(77, 174, 255);
      ofDrawBitmapString("Achieventment",100,830 );
        luck_line.draw();
        ofSetColor(255, 50, 50 );
        ofDrawBitmapString("Emotion",100,850 );
         emotion_line.draw();
        ofSetColor(255, 140, 50);
         ofDrawBitmapString("Relationship",100,870 );
         relationship_line.draw();
        ofSetColor(255);
    }
    
    if(ifdetect){
        
        btn_galaxy.load("Buttons/Galaxy.png");
        btn_galaxy.draw(430,924,889,36);
        face_btn.draw(1600,100,40,40);
    }else if(showrecord){
        
        btn_galaxy.load("Buttons/Gallary.png");
        btn_galaxy.draw(438.5,924,886,36);
        
    }else if(showdata){
        
        lab.draw(0,0);
        
     
        btn_galaxy.load("Buttons/Lab.png");
        btn_galaxy.draw(430,924,886,36);
        
        
        
      ofPopMatrix;
//       ofTranslate(ofGetWidth()*0.45,0);
        
         ofPushMatrix;
    }
    
//     ofRect(1275,920,60,40);
//     ofRect(855,920,60,40);
//     ofRect(430,920,60,40);
//    ofRect(1600,100,40,40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'x'){
//        img.saveImage("screenshot.png");

//        records[record_index].save("screenshot.png");
       
       emotion_line.addVertex(record_index*30+200,850+ofMap(param.colh,80,255,0,50));
        relationship_line.addVertex(record_index*30+200,850+ ofMap(param.degree,9,25,0,50));
        luck_line.addVertex(record_index*30+200, 850+ofMap(param.dens,20,200,0,50));
        bSnapshot = true;

       
    }
    if(key =='s'){
        
        ofSetWindowShape(1920,1000);
       
        
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(y>920){
        if(x< 520 && x>430 ){
            
            showrecord =false;
            ifdetect = true;
                showdata= false;
//            btn_gallary.load("Buttons/Off_Gallary.png");
//            btn_lab.load("Buttons/Off_Lab.png");
//            btn_gallary.draw(860,924,67.8,22.2);
//            btn_lab.draw(1280,924,32.4,17.4);
        }else if (x< 928 && x>855){
            showrecord =true;
            ifdetect = false;
             showdata= false;
//            btn_galaxy.load("Buttons/Gallary.png");
//            btn_galaxy.draw(523.5,924,886,36);
//            btn_gallary.load("Buttons/On_Gallary.png");
//            btn_lab.load("Buttons/Off_Lab.png");
//            btn_gallary.draw(860,924,74.4,31.8);
//            btn_lab.draw(1280,924,32.4,17.4);
            
        }else if (x<1335 && x >1275){
            showrecord =false;
            ifdetect = false;
                       showdata=true;
//            btn_galaxy.load("Buttons/Lab.png");
//            btn_galaxy.draw(517,924,886,36);
//
            
        }

            
            
//            btn_galaxy.draw(440,924,72,31.8);
//        btn_gallary.load("Buttons/Off_Gallary.png");
//        btn_lab.load("Buttons/Off_Lab.png");
//        btn_gallary.draw(860,924,67.8,22.2);
//        btn_lab.draw(1280,924,32.4,17.4);
    }
    
    
    if(y>80 && y <160 ){
        
    if(x>1580 && x<1660){
//        ofPopMatrix;
        //       ofTranslate(ofGetWidth()*0.45,0);
        if(is_faceshow) is_faceshow =false;
            else is_faceshow =true;
        
//        ofPushMatrix;
  
    }}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
static std::vector<float> createGaussianWeights(int radius, float variance) {
    
    int rowSize = 1 + radius;
    float sum = 0.f;
    std::vector<float> row;
    
    for (int i = 0; i < rowSize; i++) {
        
        float x = ofMap(i, 0, radius, 0, 1.2f);
        float w = Gaussian(x, 0, variance);
        
        row.push_back(w);
        
        if (i != 0) w *= 2.f;
        sum += w;
    }
    
    for (int i = 0; i < row.size(); i++) {
        row[i] /= sum;
    }
    
    return row;
}

static float Gaussian(float x, float mean, float variance) {
    x -= mean;
    return (1. / sqrt(TWO_PI * variance)) * exp(-(x * x) / (2. * variance));
}
