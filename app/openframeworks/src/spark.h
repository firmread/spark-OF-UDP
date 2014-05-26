//
//  spark.h
//  mainApp
//
//  Created by Firm Read on 5/26/14.
//
//

#ifndef __mainApp__spark__
#define __mainApp__spark__

#include <iostream>
#include "ofMain.h"
#include "ofxNetwork.h"
#include "communicationTypes.h"
#include "communicationDefines.h"
#include "timer.h"

class spark{
public:
    
//    void setup();
    spark();
    void init();
    void update();
    void draw(int x, int y);
     
//    void sendPacketToSpark(ofToSparkyPacket o2s);
    void readPacketFromSpark(char * udpMessage);
    
    int millisAlive;
    float lastContactTime;
    int nPacketsReceived;
    
    float sendPacketOutTime;
    float getPacketBackTime;
    float deltaTimeRoundTrip;
    
    float checkRoundtripTime;
    
    string uuid;
    ofxUDPManager udp;
    string ip;
    sparkyToOFPacket s2o;
    
    timer t;
    
};



#endif /* defined(__mainApp__spark__) */
