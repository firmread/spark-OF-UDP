//
//  spark.cpp
//  mainApp
//
//  Created by Firm Read on 5/26/14.
//
//

#include "spark.h"

spark::spark(){
    transferTime = -1;
    nPacketsReceived = 0;
    heartRate = 500;
    t.setup(heartRate);
    fadingBeep = 0;
    
}

void spark::setup(sparkyToOFPacket s2oInit){
    
    udp.Create();
    udp.Connect(tempIp.c_str(),8888);
    udp.Bind(7777);
    udp.SetNonBlocking(true);
    temp.ip = tempIp;
    temp.uuid = uuid;
    temp.millisAlive = S2Opacket.millisRunning;
    temp.nPacketsReceived++;
}


void spark::update(){
    if(t.bTimerFired()){
        
    }
    
    t.setTimer(heartRate);
    
    // add timer
    // do heartbeat
    
}

void spark::draw(int x, int y){
    ofPushMatrix();
    ofTranslate(x, y);
    
    if (bGotPacket) {
        fadingBeep = 0;
        bGotPacket = false;
    }
    if (fadingBeep < 255) fadingBeep +=5;
    
    ofSetColor(255, fadingBeep, fadingBeep, 220);
    ofCircle(-15, -15, 10);
    
    ofSetColor(200);
    ofDrawBitmapString(   "uuid    :" + ofToString(uuid) +
                        "\nip      :" + ofToString(ip) +
                        "\nmsAlive :" + ofToString(millisAlive) +
                        "\npkg recv:" + ofToString(nPacketsReceived) +
                        "\ntransfT :" + ofToString(transferTime), 0,0);
    
    ofPopMatrix();
    
}


//void spark::sendPacketToSpark(ofToSparkyPacket o2s){
//    
//}

void spark::readPacketFromSpark(char * udpMessage){
    
    bGotPacket = true;
    //pass data to local variables
    memset(&s2o, 0, sizeof(sparkyToOFPacket));
    memcpy(&s2o, udpMessage, sizeof(sparkyToOFPacket));
    
    //time
    millisAlive = s2o.millisRunning;
    
    //transfer time
    transferTime = s2o.ofPacketSentOutTime - ofGetElapsedTimef();
    
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