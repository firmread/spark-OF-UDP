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
#include "getOfLocalIp.h"
#include "packetHandler.h"

class spark{
public:
    
//    void setup();
    spark();
    
    void setup(sparkyToOFPacket s2oInit);
    void update();
    void draw(int x, int y);
     
//    void sendPacketToSpark(ofToSparkyPacket o2s);
//    void readPacketFromSpark(char * udpMessage);
    void readPacketFromSpark(sparkyToOFPacket s2oread);
    
    int millisRunning;
    float lastContactTime;
    int nPacketsReceived;
    
    float transferTime;
    
    bool bGotPacket;  
    float fadingBeep;
    
    string uuid;
    int boardNumber;
    ofxUDPManager udp;
    string ip;
    sparkyToOFPacket s2o;
    ofToSparkyPacket o2s;
    
    timer t;
    float heartRate;
    
    bool bUdpConnected;
    
};



#endif /* defined(__mainApp__spark__) */
