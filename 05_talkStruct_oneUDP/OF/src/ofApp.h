#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "communicationTypes.h"
#include "timer.h"
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
  
    ofxUDPManager udp;
//    ofxUDPManager udpSend;
//    ofxUDPManager udpRece;
    
    string line1, line2, line3;
    bool bGotSth;
    packet p;
    returnPacket rp;
    
    timer t;
    
    int delay;
    
    int ip[4];
    string uuid;
};

