#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    ofSetCircleResolution(100);
    ofToggleFullscreen();
    
    // bgm設定
    backgroundMusic.loadSound("ff13op.mp3");
    backgroundMusic.setLoop(true);
    backgroundMusic.play();
    
    // FFT初期設定
    fftSmoothed = new float[8192];
    for (int i = 0; i < 8192; i++){
        fftSmoothed[i] = 0;
    }
    nBandsToGet = 2;
    
    // 画像の読み込み
    earthImg.loadImage("image_earth.jpg");
    
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
            
            earthGrid[(int)x/15][(int)y/8] = boxGrid(ofPoint(px, py, pz), ofColor(cur, 127));
        }
    }
    
    // 地球の位置とカメラ視点初期化
    earthPosition = ofPoint(-earth_revolution_radius, 0, 0);
    moonPosition = earthPosition + ofPoint(earth_radius*1.5, 0, 0);
    cameraPosition = earthPosition + ofPoint(0, earth_radius*1.3, 0);
    
    // 星の位置を決める
    for (int i = 0; i < STAR_NUM; i++){
        float radius = ofRandom(star_radius_min, star_radius_max);
        float theta = ofRandom(TWO_PI);
        float phi = ofRandom(TWO_PI);
        starPosition[i] = polarToOrthogonal(radius, theta, phi);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    // FFT解析
    ofSoundUpdate();
    volume=ofSoundGetSpectrum(nBandsToGet);
    //FFT解析を行い、音量の平均を出す
    for (int i = 0; i < nBandsToGet; i++){
        fftSmoothed[i] *= 0.96f;
        if (fftSmoothed[i] < volume[i]) fftSmoothed[i] = volume[i];
        avgSound += fftSmoothed[i];
    }
    //volumeに値を丸める avgSound /= nBandsToGet;
    
    // 惑星の位置
    earthPosition = ofPoint(-earth_revolution_radius*cosf((float)ofGetElapsedTimef()), 0, earth_revolution_radius*sinf((float)ofGetElapsedTimef()));
    moonPosition = earthPosition + ofPoint(earth_radius*1.5*cosf((float)ofGetElapsedTimef()), 0, earth_radius*1.5*sinf((float)ofGetElapsedTimef()));
    camera.setPosition(cameraPosition);
    
    // カメラの位置更新
    if (cam_mode == 1){
        //　地球の周りを回るカメラ
        cameraPosition = earthPosition + ofPoint(0, earth_radius*1.15*cosf((float)ofGetElapsedTimef()/2), earth_radius*1.15*sinf((float)ofGetElapsedTimef()/2));
        camera.setPosition(cameraPosition);
        cameraLookAtPosition = ofPoint(earthPosition + ofPoint(0, earth_radius*1.15*cosf((float)ofGetElapsedTimef()/2+0.7), earth_radius*1.15*sinf((float)ofGetElapsedTimef()/2+0.7)));
        camera.lookAt(cameraLookAtPosition);
    } else if (cam_mode == 2){
        // 地球注目カメラ
        cameraPosition = earthPosition +  ofPoint(0, moon_radius*10*cosf((float)ofGetElapsedTimef()/2), moon_radius*10*sinf((float)ofGetElapsedTimef()/2));
        camera.setPosition(cameraPosition);
        camera.lookAt(earthPosition);
    } else if (cam_mode == 3){
        // 月注目カメラ
        cameraPosition = moonPosition +  ofPoint(0, moon_radius*5*cosf((float)ofGetElapsedTimef()/2), moon_radius*5*sinf((float)ofGetElapsedTimef()/2));
        camera.setPosition(cameraPosition);
        camera.lookAt(moonPosition);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofNoFill();
    
    // カメラ開始
    if (cam_mode == 0){
        cam.begin();
    } else {
        camera.begin();
    }
    
    ofSetColor(255);
    
    // 太陽
    for (int j = 0; j < 20; j++){
        float angle = PI/40.0f*j;
        ofSetColor(ofColor::fromHsb(20*pow(sin(ofGetElapsedTimef() + PI/600*j), 2), 255, 255, 127));
        for (int i = 0; i < 80*cos(angle); i++){
            ofPushMatrix();
            ofRotateX(360.0/(80.0*cos(angle))*i);
            ofRotateY(angle/PI*180);
            ofDrawBox(polarToOrthogonal(sun_radius, 0, 0), 15, 15, ofRandom(0, 30));
            ofRotateY(-2*angle/PI*180);
            if (angle != 0){
                ofDrawBox(polarToOrthogonal(sun_radius, 0, 0), 15, 15, ofRandom(0, 30));
            }
            ofPopMatrix();
        }
    }
    
    // 月
    ofPushMatrix();
    ofTranslate(moonPosition);
    ofRotate(45, 45, 0, 0);
    for (int j = 0; j < 5; j++){
        float angle = PI/10.0f*j;
        ofSetColor(ofColor::fromHsb(30 + 10*pow(sin(ofGetElapsedTimef() + PI/20*j), 2), 255, 255, 127));
        for (int i = 0; i < 20*cos(angle); i++){
            ofPushMatrix();
            ofRotateX(360.0/(20.0*cos(angle))*i);
            ofRotateY(angle/PI*180);
            ofCircle(polarToOrthogonal(moon_radius, 0, 0), ofRandom(5, 10));
            ofRotateY(-2*angle/PI*180);
            if (angle != 0){
                ofCircle(polarToOrthogonal(moon_radius, 0, 0), ofRandom(5, 10));
            }
            ofPopMatrix();
        }
    }
    ofPopMatrix();

    // 地球
    ofPushMatrix();
    ofTranslate(earthPosition);
    ofRotateY(90);
    for (int y = 0; y < 40; y++){
        for (int x = 0; x < 41; x++){
            ofPushMatrix();
            ofTranslate(earthGrid[x][y].getStartPoint());
            
            if ((int)earthGrid[x][y].getBoxColor().r < 40){
                ofSetColor(ofColor::fromHsb(100 + 10 * cosf(ofGetElapsedTimef()), 255, 255, 127));

            } else {
                ofSetColor(ofColor::fromHsb(160 + 30 * sinf(ofGetElapsedTimef()/5), 255, 255, 127));
            }
            
            ofDrawBox(0, 0, 0, earthGrid[x][y].getBottomWidth(), earthGrid[x][y].getBottomHeight(), 3);
            ofPopMatrix();
        }
    }
    ofPopMatrix();
    
    // 公転軌道の線描画モード
    if (revolution_line){
        ofSetLineWidth(0.1);
        ofSetColor(60);
        // 地球
        ofPushMatrix();
        ofRotateX(90);
        ofCircle(0, 0, earth_revolution_radius);
        ofPopMatrix();
    }
    
    // 設定された星の位置に三角・四角で星を描画
    for (int i = 0; i < STAR_NUM; i++){
        ofPushMatrix();
        ofRotateX(i);
        ofRotateY(i);
        ofSetColor(ofColor::fromHsb(255.0/6 + 10 * sin(ofGetElapsedTimeMillis()/100 + i*PI/300), 255, 255, 120));
        float randomf = ofRandom(1);
        if (randomf < 0.34){
            ofCircle(starPosition[i], ofRandom(10, fftSmoothed[1] * 6000));
        } else if (randomf < 0.68){
            ofRect(starPosition[i], ofRandom(10, fftSmoothed[1] * 6000), ofRandom(10, fftSmoothed[1] * 6000));
        }
        ofPopMatrix();
    }
    
    // カメラ終了
    if (cam_mode == 0){
        cam.end();
    } else {
        camera.end();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key){
        case ' ':
            cam_mode = (cam_mode + 1) % 4;
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




