//
//  packetHandler.cpp
//  mainApp
//
//  Created by Firm Read on 5/27/14.
//
//

#include "packetHandler.h"

packetHandler::packetHandler(ofToSparkyPacket o2s){
    bIsO2S = true;
    
    packetType = o2s.packetType;
    millisRunning = -1;
    ofPacketSentOutTime = o2s.ofPacketSentOutTime;
    
    uuid = -1;
    
    ipSparkString = -1;
    ipSparkInt = -1;
    
}


packetHandler::packetHandler(sparkyToOFPacket s2o){
    bIsO2S = false;
    //-1 = spark to of
    packetType = -1;
    millisRunning = s2o.millisRunning;
    ofPacketSentOutTime = s2o.ofPacketSentOutTime;
    
    string temp( s2o.uuid, s2o.uuid + sizeof s2o.uuid / sizeof s2o.uuid[0] );
    uuid = temp;
    
    
    int ip[4];
    ip[0] = s2o.ipSpark >> 24 & 0xFF;
    ip[1] = s2o.ipSpark >> 16 & 0xFF;
    ip[2] = s2o.ipSpark >> 8 & 0xFF;
    ip[3] = s2o.ipSpark & 0xFF;
    
    ipSparkString = ofToString(ip[0]) + "." + ofToString(ip[1]) + "."
    + ofToString(ip[2]) + "." + ofToString(ip[3]);
    
    ipSparkInt = s2o.ipSpark;
    
}