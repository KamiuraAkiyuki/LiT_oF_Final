#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    ofToggleFullscreen();
    
    // 地球画像の読み込み
    earthImg.loadImage("image_earth.jpg");
    
    // 地球グリッドに値を代入
    for(int y = 0; y < (int)earthImg.getHeight(); y += 5){
        for(int x = 0; x < (int)earthImg.getWidth(); x += 10){
            ofColor cur = earthImg.getColor(x, y);
            
            float theta = (float)y * M_PI / earthImg.getHeight();
            float phi = (float)x * 2.0 * M_PI / earthImg.getWidth();
            float px = earth_radius * sin(theta) * cos(phi);
            float py = earth_radius * sin(theta) * sin(phi);
            float pz = earth_radius * cos(theta);
            
            grid[(int)x/10][(int)y/5] = boxGrid(ofPoint(px, py, pz), ofColor(cur, 127));
        }
    }
    
    cout << earthImg.getHeight() << endl;
    
    // 地球の位置とカメラ視点初期化
    earthPosition = ofPoint(-700, 0, 0);
    cameraPosition = earthPosition + ofPoint(0, earth_radius*1.3, 0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // 地球の位置とカメラの位置更新
    earthPosition = ofPoint(-700*cosf((float)ofGetElapsedTimef()), 0, 700*sinf((float)ofGetElapsedTimef()));
    cameraPosition = earthPosition + ofPoint(0, earth_radius*1.15*cosf((float)ofGetElapsedTimef()/2), earth_radius*1.15*sinf((float)ofGetElapsedTimef()/2));
    camera.setPosition(cameraPosition);
    cameraLookAtPosition = ofPoint(earthPosition + ofPoint(0, earth_radius*1.15*cosf((float)ofGetElapsedTimef()/2+0.7), earth_radius*1.15*sinf((float)ofGetElapsedTimef()/2+0.7)));
    camera.lookAt(cameraLookAtPosition);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofNoFill();
    
    if (camMode == 0){
        camera.begin();
    } else if (camMode == 1){
        cam.begin();
    }
    
    ofSetColor(255);
    
    // 太陽
    for (int j = 0; j < 30; j++){
        float angle = PI/60.0f*j;
        ofSetColor(ofColor::fromHsb(20*pow(sin(ofGetElapsedTimef() + PI/600*j), 2), 255, 255, 127));
        for (int i = 0; i < 120*cos(angle); i++){
            ofPushMatrix();
            ofRotateX(360.0/(120.0*cos(angle))*i);
            ofRotateY(angle/PI*180);
            ofDrawBox(polarToOrthogonal(sun_radius, 0, 0), 10, 10, ofRandom(0, 20));
            ofRotateY(-2*angle/PI*180);
            if (angle != 0){
                ofDrawBox(polarToOrthogonal(sun_radius, 0, 0), 10, 10, ofRandom(0, 20));
            }
            ofPopMatrix();
        }
    }
    
    // 地球
    ofPushMatrix();
    ofTranslate(earthPosition);
    ofRotateY(90);
    for (int y = 0; y < 62; y++){
        for (int x = 0; x < 61; x++){
            ofPushMatrix();
            ofTranslate(grid[x][y].getStartPoint());
            
            if ((int)grid[x][y].getBoxColor().r < 40){
                ofSetColor(ofColor::fromHsb(100 + 10 * cosf(ofGetElapsedTimef()), 255, 255, 127));

            } else {
                ofSetColor(ofColor::fromHsb(160 + 30 * sinf(ofGetElapsedTimef()/5), 255, 255, 127));
            }
            
            ofDrawBox(0, 0, 0, grid[x][y].getBottomWidth(), grid[x][y].getBottomHeight(), 3);
            ofPopMatrix();
        }
    }
    ofPopMatrix();
    
    if (camMode == 0){
        camera.end();
    } else if (camMode == 1){
        cam.end();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key){
        case ' ':
            camMode = (camMode + 1)%2;
            break;
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

//--------------------------------------------------------------

// 極座標を直交座標に変換する関数(引数はラジアン値)
ofPoint ofApp::polarToOrthogonal(float radius, float angle1, float angle2){
    ofPoint orthogonalPoint;
    orthogonalPoint.x = radius * sinf(angle1) * cosf(angle2);
    orthogonalPoint.y = radius * sinf(angle1) * sinf(angle2);
    orthogonalPoint.z = radius * cosf(angle1);
    return orthogonalPoint;
}

ofPoint ofApp::orthogonalToPolar(float x, float y, float z){
    ofPoint polarPoint;
    polarPoint.x = sqrt(x * x + y * y + z * z);
    polarPoint.y = acos(z / polarPoint.x);
    polarPoint.z = atan2(y, x);
}




