#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    ofSetCircleResolution(100);
    ofToggleFullscreen();
    
    // 画像の読み込み
    mercuryImg.loadImage("mercury.jpg");
    earthImg.loadImage("image_earth.jpg");
    
    // 水星にグリッドを設定
    cout << "mercuryW: " << mercuryImg.getWidth()/25 << endl;
    cout << "mercuryH: " << mercuryImg.getHeight()/20 << endl;
    for(int y = 0; y < (int)mercuryImg.getHeight(); y += 20){
        for(int x = 0; x < (int)mercuryImg.getWidth(); x += 25){
            ofColor cur = mercuryImg.getColor(x, y);
            
            float theta = (float)y * M_PI / mercuryImg.getHeight();
            float phi = -(float)x * 2.0f * M_PI / mercuryImg.getWidth();
            float px = mercury_radius * sin(theta) * cos(phi);
            float py = mercury_radius * sin(theta) * sin(phi);
            float pz = mercury_radius * cos(theta);
            
            mercury[(int)x/25][(int)y/20] = boxGrid(ofPoint(px, py, pz), ofColor(cur, 127));

        }
    }

    // 地球グリッドに値を代入
    cout << "earthH: " << (int)earthImg.getHeight()/8 << endl;
    cout << "earthW: " << (int)earthImg.getWidth()/15 << endl;
    for(int y = 0; y < (int)earthImg.getHeight(); y += 8){
        for(int x = 0; x < (int)earthImg.getWidth(); x += 15){
            ofColor cur = earthImg.getColor(x, y);
            
            float theta = (float)y * M_PI / earthImg.getHeight();
            float phi = (float)x * 2.0 * M_PI / earthImg.getWidth();
            float px = earth_radius * sin(theta) * cos(phi);
            float py = earth_radius * sin(theta) * sin(phi);
            float pz = earth_radius * cos(theta);
            
            grid[(int)x/15][(int)y/8] = boxGrid(ofPoint(px, py, pz), ofColor(cur, 127));
        }
    }
    
    
    
    // 地球の位置とカメラ視点初期化
    earthPosition = ofPoint(-earth_revolution_radius, 0, 0);
    mercuryPosition = ofPoint(-mercury_revolution_radius, 0, 0);
    cameraPosition = earthPosition + ofPoint(0, earth_radius*1.3, 0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // 惑星の位置
    earthPosition = ofPoint(-earth_revolution_radius*cosf((float)ofGetElapsedTimef()), 0, earth_revolution_radius*sinf((float)ofGetElapsedTimef()));
    mercuryPosition = ofPoint(-mercury_revolution_radius*cosf((float)ofGetElapsedTimef()), 0, mercury_revolution_radius*sinf((float)ofGetElapsedTimef()));
    
    
    // カメラの位置更新
    cameraPosition = earthPosition + ofPoint(0, earth_radius*1.15*cosf((float)ofGetElapsedTimef()/2), earth_radius*1.15*sinf((float)ofGetElapsedTimef()/2));
    camera.setPosition(cameraPosition);
    cameraLookAtPosition = ofPoint(earthPosition + ofPoint(0, earth_radius*1.15*cosf((float)ofGetElapsedTimef()/2+0.7), earth_radius*1.15*sinf((float)ofGetElapsedTimef()/2+0.7)));
    camera.lookAt(cameraLookAtPosition);
    
    // メッシュの更新
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofNoFill();
    
    if (cam_mode == 0){
        cam.begin();
    } else if (cam_mode == 1){
        camera.begin();
    }
    
    ofSetColor(255);
    
    // 太陽
    for (int j = 0; j < 25; j++){
        float angle = PI/50.0f*j;
        ofSetColor(ofColor::fromHsb(20*pow(sin(ofGetElapsedTimef() + PI/600*j), 2), 255, 255, 127));
        for (int i = 0; i < 100*cos(angle); i++){
            ofPushMatrix();
            ofRotateX(360.0/(100.0*cos(angle))*i);
            ofRotateY(angle/PI*180);
            ofDrawBox(polarToOrthogonal(sun_radius, 0, 0), 10, 10, ofRandom(0, 30));
            ofRotateY(-2*angle/PI*180);
            if (angle != 0){
                ofDrawBox(polarToOrthogonal(sun_radius, 0, 0), 10, 10, ofRandom(0, 30));
            }
            ofPopMatrix();
        }
    }
    
    // 水星
//    ofPushMatrix();
//    ofTranslate(mercuryPosition);
//    ofRotateY(90);
//    for (int y = 0; y < 33; y++){
//        for (int x = 0; x < 37; x++){
//            ofPushMatrix();
//            ofTranslate(grid[x][y].getStartPoint());
//            ofSetColor(mercury[x][y].getBoxColor());
//            ofDrawBox(0, 0, 0, mercury[x][y].getBottomWidth(), grid[x][y].getBottomHeight(), 1);
//            ofPopMatrix();
//        }
//    }
//    ofPopMatrix();
    
    // 地球
    ofPushMatrix();
    ofTranslate(earthPosition);
    ofRotateY(90);
    for (int y = 0; y < 40; y++){
        for (int x = 0; x < 41; x++){
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
    
    // 公転軌道の線描画モード
    if (revolution_line){
        ofSetLineWidth(0.1);
        ofSetColor(255);
        // 地球
        ofPushMatrix();
        ofRotateX(90);
//        ofCircle(0, 0, mercury_revolution_radius);
        ofCircle(0, 0, earth_revolution_radius);
        ofPopMatrix();
    }
    
    if (cam_mode == 0){
        cam.end();
    } else if (cam_mode == 1){
        camera.end();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key){
        case ' ':
            cam_mode = (cam_mode + 1)%2;
            break;
        case 'l':
            revolution_line = !revolution_line;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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




