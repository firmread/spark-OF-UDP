//
//  spark.cpp
//  mainApp
//
//  Created by Firm Read on 5/26/14.
//
//

#include "spark.h"

spark::spark(){
    deltaTimeRoundTrip = -1;
    nPacketsReceived = 0;
    t.setup(500);
}

void spark::update(){
    if(t.bTimerFired()){
        
    }
    
    // add timer
    // do heartbeat
    
}

void spark::draw(int x, int y){
    ofPushMatrix();
    ofTranslate(x, y);
    
    ofDrawBitmapStringHighlight(  "uuid    :" + ofToString(uuid) +
                                "\nip      :" + ofToString(ip) +
                                "\nmsAlive :" + ofToString(millisAlive) +
                                "\npkg recv:" + ofToString(nPacketsReceived) +
                                "\ndeltaT  :" + ofToString(deltaTimeRoundTrip), 0,0);
    
    ofPopMatrix();
}


//void spark::sendPacketToSpark(ofToSparkyPacket o2s){
//    
//}

void spark::readPacketFromSpark(char * udpMessage){
    //pass data to local variables
    memset(&s2o, 0, sizeof(sparkyToOFPacket));
    memcpy(&s2o, udpMessage, sizeof(sparkyToOFPacket));
    
    //time
    millisAlive = s2o.millisRunning;
    
    //ip
    ip[0] = s2o.ipSpark >> 24 & 0xFF;
    ip[1] = s2o.ipSpark >> 16 & 0xFF;
    ip[2] = s2o.ipSpark >> 8 & 0xFF;
    ip[3] = s2o.ipSpark & 0xFF;
    
    string ip = ofToString(ip[0]) + "." + ofToString(ip[1]) + "."
    + ofToString(ip[2]) + "." + ofToString(ip[3]);
    
    //uuid
    string temp( s2o.uuid, s2o.uuid + sizeof s2o.uuid / sizeof s2o.uuid[0] );
    uuid = temp;
    
    
    
}