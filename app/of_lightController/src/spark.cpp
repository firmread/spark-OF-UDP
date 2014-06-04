//
//  spark.cpp
//  mainApp
//
//  Created by Firm Read on 5/26/14.
//
//

#include "spark.h"
#include "sparkPacketUtils.h"
#include "ofApp.h"


spark::spark(){
    transferTime = -1;
    nPacketsReceived = 0;
    fadingBeep = 0;
    bSendHeartBeat = false;
    
}

void spark::setup(sparkyToOFPacket & s2oInit){
    ip = ipFromInt(s2oInit.ipSpark);
    uuid = uuidFromCharArray(s2oInit.uuid);
    millisRunning = s2oInit.millisRunning;
    transferTime = ofGetElapsedTimef() - s2oInit.ofPacketSentOutTime;
    nPacketsReceived = 1;
    sparkSentCount = 0;

    packetPerSecond.setup();
    missedPerSecond.setup();
    outOfOrderPerSecond.setup();
    
    packetPerSecond.min = 0;
    packetPerSecond.max = 90.0;
    
    missedPerSecond.min = 0;
    missedPerSecond.max = 10;
    
    outOfOrderPerSecond.min = 0;
    outOfOrderPerSecond.max = 10;
    
}


void spark::update(){
    
    // heartbeat flag:
    
    if (bSendHeartBeat){
        bSendHeartBeat = false;
        memset(&o2s, 0, sizeof(ofToSparkyPacket));
        o2s.packetType = PACKET_TYPE_HEARTBEAT;
        o2s.ofIp = ((ofApp *) ofGetAppPtr())->myIPaddressInt;
        char packetBytes[sizeof(ofToSparkyPacket)];
        o2s.ofPacketSentOutTime = ofGetElapsedTimef();
        o2s.packetCount = sparkSentCount++;
        memcpy(packetBytes, &o2s, sizeof(ofToSparkyPacket));
        udp.Create();
        udp.Connect(ip.c_str(), 8888);
        int sent =  udp.Send(packetBytes, sizeof(ofToSparkyPacket));
        udp.Close();
    }
}

void spark::draw(int x, int y){
    
    ofPushMatrix();
    ofTranslate(x, y);
    
    if (bGotPacket) {
        fadingBeep = 0;
        bGotPacket = false;
    }
    if (fadingBeep < 255) fadingBeep +=5;
    
    ofFill();
    ofSetColor(255, fadingBeep, fadingBeep, 220);
    ofCircle(-15, -15, 10);
    
    ofSetColor(200);
    ofDrawBitmapString(   "uuid    :" + ofToString(uuid) +
                        "\nip      :" + ofToString(ip) +
                        "\nmsAlive :" + ofToString(millisRunning) +
                        "\npkg recv:" + ofToString(nPacketsReceived) +
                        "\ntransfT :" + ofToString(transferTime) +
                        "\nbordNum :" + ofToString(boardNumber), 0,0);
    
    ofPopMatrix();
    
   
    
}


void spark::drawSmall(int x, int y){
    ofPushMatrix();
    ofTranslate(x, y);
    
    if (bGotPacket) {
        fadingBeep = 0;
        bGotPacket = false;
    }
    if (fadingBeep < 255) fadingBeep +=5;
    
    ofFill();
    ofSetColor(255, fadingBeep, fadingBeep, 220);
    ofCircle(-15,0, 10);
    
    ofSetColor(200);
    ofDrawBitmapString(
                       "ip: " + ofToString(ip) +
                       " pkg recv: " + ofToString(nPacketsReceived) +
                       " transfT: " + ofToString(transferTime) +
                       " bordNum: " + ofToString(boardNumber), 0,0);
    
    
    packetPerSecond.draw( ofRectangle(400,0, 50, 20) );
    missedPerSecond.draw( ofRectangle(500,0, 50, 20) );
    outOfOrderPerSecond.draw( ofRectangle(600,0, 50, 20) );
    
    ofPopMatrix();
    
}


void spark::readPacketFromSpark(sparkyToOFPacket & s2oRead, float readTime){

    bGotPacket = true;
    millisRunning = s2oRead.millisRunning;
    uuid = uuidFromCharArray(s2oRead.uuid);
    nPacketsReceived++;
    transferTime = readTime - s2oRead.ofPacketSentOutTime;
    
    packetPerSecond.addValue(s2oRead.sparkDataFrameRate);
    missedPerSecond.addValue(s2oRead.missedPacketPerSecond );
    outOfOrderPerSecond.addValue(s2oRead.outOfOrderPerSecond);
    
    
    
    cout << s2oRead.sparkDataFrameRate << "  out of order " <<  s2oRead.missedPacketPerSecond   <<  " missed " << s2oRead.outOfOrderPerSecond << endl;
}