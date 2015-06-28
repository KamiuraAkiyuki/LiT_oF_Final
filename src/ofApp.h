#pragma once

#include "ofMain.h"
#include "boxGrid.h"

#define GRID_NUM 1000

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
        float mercury_radius = 4879.4 / 200.0;
        float venus_radius = 12103.6 / 200.0;
        float earth_radius = 12756.27 / 200.0;
        float mers_radius = 6794.4  / 200.0;
        float jupiter_radius = 142984.0 / 200;
        float saturn_radius = 120536.0 / 200;
        float uranus_radius = 51118.0 / 200;
        float neptune_radius = 40528.0 / 200;
    
        // 公転周期の半径を設定
        float revolution_unit = 1000;
        float mercury_revolution_radius = 0.3871 * revolution_unit;
        float venus_revolution_radius = 0.7233 * revolution_unit;
        float earth_revolution_radius = 1.0 * revolution_unit;
        float mars_revolution_radius = 1.52366 * revolution_unit;
        float jupiter_revolution_radius = 5.2026 * revolution_unit;
        float saturn_revolution_radius = 9.55491 * revolution_unit;
        float uranus_revolution_radius = 19.128 * revolution_unit;
        float neptune_revolution_radius = 30.11 * revolution_unit;
    
        // 他の恒星(星)の描画
        float star_radius_min = 3000;
        float star_radius_max = 5000;
    
        // 惑星を描画する直方体の情報を持つクラスのインスタンス
        boxGrid grid[41][40];
        boxGrid mercury[37][33];
    
        // 惑星の画像
        ofImage earthImg;
        ofImage mercuryImg;
    
        // 惑星の位置
        ofPoint earthPosition;
        ofPoint mercuryPosition;

        // カメラ設定
        int cam_mode = 0;  // 0ならofEasyCam, 1ならofCamera
        ofEasyCam cam;
        ofCamera camera;
        ofPoint cameraPosition;
        ofPoint cameraLookAtPosition;
    
        // 公転軌道の線を描画するかどうか
        bool revolution_line = false;
};
