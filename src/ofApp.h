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
    
        ofPoint polarToOrthogonal(float radius, float angle1, float angle2);
        ofPoint orthogonalToPolar(float x, float y, float z);
    
        float earth_radius = 100;
        float sun_radius = 300;
        float star_radius = 5000;

        int camMode = 0;
        ofCamera camera;
        ofEasyCam cam;
        ofSpherePrimitive earthSphere;
        ofImage earthImg;
        boxGrid grid[61][62];
    
        ofPoint cameraPosition;
        ofPoint cameraLookAtPosition;
        ofPoint earthPosition;
};
