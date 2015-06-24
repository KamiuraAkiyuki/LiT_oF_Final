#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    
    ofSetColor(255);
    
    // 地球の枠の描画
    earth.setPosition(0, 0, 0);
    earth.set(EARTH_RADIUS, 8);
    earth.drawWireframe();
    
    // 地球にグリッドを描画
    for (int j = 0; j < 30; j++){
        float angle = PI/60.0*j;
        ofSetColor(ofColor::fromHsb(255*pow(sin(ofGetElapsedTimef()/10 + PI/600*j), 2), 255, 255, 127));
        for (int i = 0; i < 120*cos(angle); i++){
            ofPushMatrix();
            ofRotateX(360.0/(120.0*cos(angle))*i);
            ofRotateY(angle/PI*180);
            ofDrawBox(polarToOrthogonal(EARTH_RADIUS, 0, 0), 7, 7, ofRandom(0, 10));
            ofRotateY(-2*angle/PI*180);
            if (angle != 0){
                ofDrawBox(polarToOrthogonal(EARTH_RADIUS, 0, 0), 7, 7, ofRandom(0, 10));
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




