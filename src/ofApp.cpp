#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    earthImg.loadImage("image_earth.jpg");
    
    for(int y = 0; y < (int)earthImg.getHeight(); y += 5){
        for(int x = 0; x < (int)earthImg.getWidth(); x += 10){
            ofColor cur = earthImg.getColor(x, y);
            
            float theta = (float)y * M_PI / earthImg.getHeight();
            float phi = (float)x * 2.0f * M_PI / earthImg.getWidth();
            float px = EARTH_RADIUS * sin(theta) * cos(phi);
            float py = EARTH_RADIUS * sin(theta) * sin(phi);
            float pz = EARTH_RADIUS * cos(theta);
            
            gridPos[x/10][y/5] = boxGrid(ofPoint(px, py, pz), cur);
        }
    }
    
    ofSetVerticalSync(true);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    mySound.loadSound("Spring of Life.mp3");
    mySound.setLoop(true);
    mySound.play();
    // FFT解析初期化
    fftSmoothed = new float[8192];
    for (int i = 0; i < 8192; i++){
        fftSmoothed[i] = 0;
    }
    nBandsToGet = 32;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSoundUpdate();
    volume = ofSoundGetSpectrum(nBandsToGet);
    //FFT解析を行い、音量の平均を出す
    for (int i = 0; i < nBandsToGet; i++){
        fftSmoothed[i] *= 0.96f;
        if (fftSmoothed[i] < volume[i]) fftSmoothed[i] = volume[i];
        avgSound += fftSmoothed[i];
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    
    ofSetColor(255);
    
    // 地球の枠の描画
    ofPushMatrix();
    ofRotateX(90);
    earth.setPosition(0, 0, 0);
    earth.set(EARTH_RADIUS, 8);
    earth.drawWireframe();
    ofPopMatrix();
    
    // 地球にグリッドを描画(均等に近い)
//    for (int j = 0; j < 30; j++){
//        float angle = PI/60.0*j;
//        ofSetColor(ofColor::fromHsb(255*pow(sin(ofGetElapsedTimef()/10 + PI/600*j), 2), 255, 255, 127));
//        for (int i = 0; i < 120*cos(angle); i++){
//            ofPushMatrix();
//            ofRotateX(360.0/(120.0*cos(angle))*i);
//            ofRotateY(angle/PI*180);
//            ofDrawBox(polarToOrthogonal(EARTH_RADIUS, 0, 0), 7, 7, ofRandom(0, 10));
//            ofRotateY(-2*angle/PI*180);
//            if (angle != 0){
//                ofDrawBox(polarToOrthogonal(EARTH_RADIUS, 0, 0), 7, 7, ofRandom(0, 10));
//            }
//            ofPopMatrix();
//        }
//    }
    
    // 画像から情報を読み取った場合
    for (int y = 0; y < 62; y++){
        for (int x = 0; x < 61; x++){
            ofPushMatrix();
            ofTranslate(gridPos[x][y].getStartPoint());
            ofSetColor(gridPos[x][y].getBoxColor(), 127);
            if (x < 32){
                ofDrawBox(0, 0, 0, gridPos[x][y].getBottomWidth(), gridPos[x][y].getBottomHeight(), fftSmoothed[x]);
            } else {
                ofDrawBox(0, 0, 0, gridPos[x][y].getBottomWidth(), gridPos[x][y].getBottomHeight(), 0);
            }
            ofPopMatrix();
        }
    }
    
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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


// 極座標を直交座標に変換する関数(引数はラジアン値)
ofPoint ofApp::polarToOrthogonal(float radius, float angle1, float angle2){
    ofPoint orthogonalPoint;
    orthogonalPoint.x = radius * sinf(angle1) * cosf(angle2);
    orthogonalPoint.y = radius * sinf(angle1) * sinf(angle2);
    orthogonalPoint.z = radius * cosf(angle1);
    return orthogonalPoint;
}




