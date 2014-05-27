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
    

    
//    udp.Create();
//    udp.Connect(tempIp.c_str(),8888);
//    udp.Bind(7777);
//    udp.SetNonBlocking(true);
//    temp.ip = tempIp;
//    temp.uuid = uuid;
//    temp.millisAlive = S2Opacket.millisRunning;
//    temp.nPacketsReceived++;
}


void spark::update(sparkyToOFPacket s2oRead){
    //beat
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
                        "\nmsAlive :" + ofToString(millisRunning) +
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
    
    packetHandler ph;
    ph.parse(s2o);
    millisRunning = ph.millisRunning;
    uuid = ph.uuid;
    
    ip = ph.ipSparkString;
    
    
    
}