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
    heartRate = 2000;
    t.setup(heartRate);
    fadingBeep = 0;
    bSendHeartBeat = false;
    
}

void spark::setup(sparkyToOFPacket & s2oInit){
    
    
    bUdpConnected = false;
 
    //udp.Create();
    //bUdpConnected = udp.Connect(ph.ipSparkString.c_str(), 8888);
    //udp.SetNonBlocking(true);
    
    ip = ipFromInt(s2oInit.ipSpark);
    uuid = uuidFromCharArray(s2oInit.uuid);
    millisRunning = s2oInit.millisRunning;
    
    transferTime = ofGetElapsedTimef() - s2oInit.ofPacketSentOutTime;
    
    nPacketsReceived = 1;
    sparkSentCount = 0;

}


void spark::update(){
    
    
    //cout << ip << " " << bUdpConnected << endl;
//    if (!bUdpConnected){
//        cout << "trying again to connect ??? " << endl;
//        bUdpConnected = udp.Connect(ip.c_str(), 8888);
//        return;
//        
//    }
    
    //beat
    
//    t.setTimer(heartRate);
//    t.update(ofGetElapsedTimeMillis());
//    if(t.bTimerFired()){
    if (bSendHeartBeat){
        bSendHeartBeat = false;
        memset(&o2s, 0, sizeof(ofToSparkyPacket));
        o2s.packetType = PACKET_TYPE_HEARTBEAT;
        
        //getOfLocalIp readIp;
        o2s.ofIp = ((ofApp *) ofGetAppPtr())->myIPaddressInt;
        
        char packetBytes[sizeof(ofToSparkyPacket)];
        o2s.ofPacketSentOutTime = ofGetElapsedTimef();
        o2s.packetCount = sparkSentCount++;
        
        memcpy(packetBytes, &o2s, sizeof(ofToSparkyPacket));

        //int sent = udp.Send(packetBytes,sizeof(ofToSparkyPacket));
        //cout << ip << " " << sent << endl;
        
        udp.Create();
        udp.Connect(ip.c_str(), 8888);
        int sent =  udp.Send(packetBytes, sizeof(ofToSparkyPacket));
        //cout << sent << " " << ip << endl;
        udp.Close();
        
        //if (sent == -1){
         //   udp.Close();
         //   udp.Create();
         //   bUdpConnected = udp.Connect(ip.c_str(), 8888);
       // }

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
    
    ofPopMatrix();
    
}


//void spark::sendPacketToSpark(ofToSparkyPacket o2s){
//    
//}

//void spark::readPacketFromSpark(char * udpMessage){
void spark::readPacketFromSpark(sparkyToOFPacket & s2oRead, float readTime){

    bGotPacket = true;
//    //pass data to local variables
//    memset(&s2o, 0, sizeof(sparkyToOFPacket));
//    memcpy(&s2o, udpMessage, sizeof(sparkyToOFPacket));

    //packetHandler ph(s2oRead);
    millisRunning = s2oRead.millisRunning;
    uuid = uuidFromCharArray(s2oRead.uuid);
    nPacketsReceived++;
    transferTime = readTime - s2oRead.ofPacketSentOutTime;
    cout << s2oRead.sparkDataFrameRate << "  out of order " <<  s2oRead.missedPacketPerSecond   <<  " missed " << s2oRead.outOfOrderPerSecond << endl;
}