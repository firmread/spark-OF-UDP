#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "timer.h"
#include "spark.h"
#include "getOfLocalIp.h"
#include "packetHandler.h"
#include "../../common/communicationDefines.h"
#include "../../common/communicationTypes.h"
#include "ofxGui.h"
#include "ofxOsc.h"

// OSC
#define PORT 12345

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

    //listen to all new faces
    ofxUDPManager udp;
    //handle known sparks,, old faces
    vector < spark > sparks;

    bool bGotSth;
    
    //discovery
    ofToSparkyPacket O2Spacket;
    //heartbeat
    sparkyToOFPacket S2Opacket;

    
    ofxUDPManager udp4discovery;

    timer heart;
    timer colorTimer;
    int delay;
    string convertIpToString(int ip);
    void fireDiscovery();
    void sendColorData();
    
    // UUID
    void loadUUIDList();
    map < string, int > uuidMapping;
    
    // gui:
    
    ofxToggle   useOsc;
    ofxToggle   sendColor;
    ofxToggle   sendHeartbeat;
    ofxToggle   sendOneHeartbeat;
    ofxToggle   flipRgb;
    ofxToggle   setAllWhite;
    ofxToggle   setAllBlack;
    ofxToggle   setAllRandom;
    ofxToggle   verticalSync;
    ofxFloatSlider   colorFrameRate;
    ofxFloatSlider   heartbeatFrameRate;
    ofxIntSlider   interpolateRate;
    
	ofxPanel    gui;
    
    // OSC
    ofxOscReceiver receiver;
    
    // colors we are sending out.
    vector < ofColor > colorValuesForOutput;
    
    string myIPaddressString;
    int myIPaddressInt;
    string myIPadressJustFirstThree;        // 192.168.10.
    

};
