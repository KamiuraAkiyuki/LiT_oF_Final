#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    
    earthImg.loadImage("image_earth.jpg");
    
    for(int y = 0; y < (int)earthImg.getHeight(); y += 5){
        for(int x = 0; x < (int)earthImg.getWidth(); x += 10){
            ofColor cur = earthImg.getColor(x, y);
            
            float theta = (float)y * M_PI / earthImg.getHeight();
            float phi = -(float)x * 2.0f * M_PI / earthImg.getWidth();
            float px = EARTH_RADIUS * sin(theta) * cos(phi);
            float py = EARTH_RADIUS * sin(theta) * sin(phi);
            float pz = EARTH_RADIUS * cos(theta);
            
            gridPos[x/10][y/5] = ofPoint(px, py, pz);
            
        }
    }

    cout << (int)earthImg.getHeight()/5;
    cout << (int)earthImg.getWidth()/10;
    
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
    ofSetColor(ofColor::fromHsb(120, 255, 255, 120));
    for (int y = 0; y < 62; y++){
        for (int x = 0; x < 61; x++){
            ofDrawBox(gridPos[x][y], 7, 7, 0);
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




