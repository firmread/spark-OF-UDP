//
//  packetHandler.h
//  mainApp
//
//  Created by Firm Read on 5/27/14.
//
//

#ifndef __mainApp__packetHandler__
#define __mainApp__packetHandler__

#include <iostream>
#include "communicationTypes.h"
#include "ofMain.h"

class packetHandler{
public:
    packetHandler(ofToSparkyPacket o2s);
    packetHandler(sparkyToOFPacket s2o);
    
    bool bIsO2S;
    
    int packetType;       // 0 = discovery 1=heartbear  2=
    int r, g, b;
    
    float millisRunning;
    float ofPacketSentOutTime;
    int ipSparkInt;
    string ipSparkString;
    string uuid;
    
    
    
    
};


#endif /* defined(__mainApp__packetHandler__) */
