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
    
    packetHandler ph(s2oInit);
//    ph.parse(s2oInit);
    
    udp.Create();
    udp.Connect(ph.ipSparkString.c_str(), 8888);
    
    udp.SetNonBlocking(true);
    ip = ph.ipSparkString;
    cout << ph.ipSparkString << endl;
    cout << "my ip is " << ip << endl;
    uuid = ph.uuid;
    millisRunning = ph.millisRunning;
    nPacketsReceived = 1;

}


void spark::update(){
    //beat
    
    t.setTimer(heartRate);
    t.update(ofGetElapsedTimeMillis());
    if(t.bTimerFired()){
        memset(&o2s, 0, sizeof(ofToSparkyPacket));
        o2s.packetType = PACKET_TYPE_HEARTBEAT;
        o2s.ofPacketSentOutTime = ofGetElapsedTimef();
        getOfLocalIp readIp;
        o2s.ofIp = readIp.getInt();
        
        char packetBytes[sizeof(ofToSparkyPacket)];
        memcpy(packetBytes, &o2s, sizeof(ofToSparkyPacket));

        udp.Send(packetBytes,sizeof(ofToSparkyPacket));

    }
    
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

//void spark::readPacketFromSpark(char * udpMessage){
void spark::readPacketFromSpark(sparkyToOFPacket s2oRead){

    bGotPacket = true;
//    //pass data to local variables
//    memset(&s2o, 0, sizeof(sparkyToOFPacket));
//    memcpy(&s2o, udpMessage, sizeof(sparkyToOFPacket));

    packetHandler ph(s2oRead);
    millisRunning = ph.millisRunning;
    uuid = ph.uuid;
    
    ip = ph.ipSparkString;
    
    nPacketsReceived++;
    transferTime = ofGetElapsedTimef() - ph.ofPacketSentOutTime;
    
}