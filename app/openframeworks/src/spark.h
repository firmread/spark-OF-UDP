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
    
    void setup(sparkyToOFPacket s2oInit);
    void update();
    void draw(int x, int y);
     
//    void sendPacketToSpark(ofToSparkyPacket o2s);
    void readPacketFromSpark(char * udpMessage);
    
    int millisAlive;
    float lastContactTime;
    int nPacketsReceived;
    
    float transferTime;
    
    bool bGotPacket;
    float fadingBeep;
    
    string uuid;
    ofxUDPManager udp;
    string ip;
    sparkyToOFPacket s2o;
    
    timer t;
    float heartRate;
    
};



#endif /* defined(__mainApp__spark__) */
