#pragma once

#include "ofMain.h"
#include "boxGrid.h"

#define GRID_NUM 1000
#define STAR_NUM 200

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        // 座標変換の関数
        ofPoint polarToOrthogonal(float radius, float angle1, float angle2);
        ofPoint orthogonalToPolar(float x, float y, float z);
    
        // 惑星の半径の設定
        float sun_radius = 1392038.0 / 4000.0;
        float earth_radius = 12756.27 / 200.0;
        float moon_radius = 4000 / 200.0;
    
        // 公転周期の半径を設定
        float revolution_unit = 1000;
        float earth_revolution_radius = 1.0 * revolution_unit;
    
        // 他の恒星(星)の描画
        float star_radius_min = 3000;
        float star_radius_max = 5000;
        ofPoint starPosition[STAR_NUM];
    
        // 惑星を描画する直方体の情報を持つクラスのインスタンス
        boxGrid earthGrid[41][40];
    
        // 惑星の画像
        ofImage earthImg;
    
        // 惑星の位置
        ofPoint earthPosition;
        ofPoint moonPosition;

        // カメラ設定
        int cam_mode = 0;  // 0ならofEasyCam, 1ならofCamera
        ofEasyCam cam;
        ofCamera camera;
        ofPoint cameraPosition;
        ofPoint cameraLookAtPosition;
    
        // 公転軌道の線を描画するかどうか
        bool revolution_line = false;
};
