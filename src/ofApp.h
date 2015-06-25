#pragma once

#include "ofMain.h"
#include "boxGrid.h"

#define GRID_NUM 1000
#define EARTH_RADIUS 300

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
    
        ofPoint polarToOrthogonal(float radius, float angle1, float angle2);
    
        ofEasyCam cam;
        ofSpherePrimitive earth;
        ofImage earthImg;
        boxGrid gridPos[122][62];
};
