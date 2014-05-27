#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "timer.h"
#include "spark.h"
#include "getOfLocalIp.h"
#include "packetHandler.h"
#include "../../common/communicationDefines.h"
#include "../../common/communicationTypes.h"


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

    
    timer t;

    int delay;
//    int getOfIpInt();
    string convertIpToString(int ip);
    void fireDiscovery();
};
