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


class graph {

public:
    
    float min;
    float max;
    int valuesToStore;
    vector < float > values;
    bool bLearnMinMaxAutomatically;
    bool smoothToMinMax;
    
    void setup(){
        bLearnMinMaxAutomatically = true;
        smoothToMinMax = true;
        min = max = 0;
        valuesToStore = 30;
    }
    
    void addValue( float val ){
        values.push_back(val);
        while (values.size() > valuesToStore) values.erase(values.begin());
        
        //float recentMin = *std::min_element(values.begin(), values.end());
        //float recentMax = *std::max_element(values.begin(), values.end());
        
        //min = 0.99f * min + 0.01 * recentMin;
        //max = 0.99f * max + 0.01 * recentMax;
        
    }
    
    void draw( ofRectangle rect ){
        ofFill();
        ofSetColor(0);
        ofRect(rect.x-2, rect.y-2, rect.width+4, rect.height+4);
        ofSetColor(80);
        ofRect(rect);
        
        ofNoFill();
        ofSetColor(255);
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
        
        for (int i = 0; i < values.size(); i++){
            mesh.addVertex( ofPoint(ofMap(i,0,values.size()-1, rect.x, rect.x+rect.width,true),
                                    ofMap(values[i], min, max, rect.y+ rect.height, rect.y, true) ));
        }
        //mesh.addVertex( ofPoint(rect.x, rect.y) + ofPoint(rect.width, rect.height));
        //mesh.addVertex( ofPoint(rect.x, rect.y) + ofPoint(rect.width, rect.height));
        
        mesh.draw();
    }
    
};


class spark{
public:
    
//    void setup();
    spark();
    
    bool bSendHeartBeat;
    int sparkSentCount;
    
    
    void setup(sparkyToOFPacket & s2oInit);
    void update();
    void draw(int x, int y);
    void drawSmall(int x, int y);
    void readPacketFromSpark(sparkyToOFPacket & s2oread, float readTime);
    
    graph packetPerSecond;
    graph missedPerSecond;
    graph outOfOrderPerSecond;
    
    
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
    ofToSparkyPacket o2s;
    
    
    
};



#endif /* defined(__mainApp__spark__) */
