//
//  recordedPulseScene.cpp
//  of_colorOscSender
//
//  Created by Firm Read on 6/11/14.
//
//

#include "recordedPulseScene.h"


void recordedPulseScene::setup(){
    
    for (int i = 0; i < 50; i++){
        val[i] = 0;
    }
}

void recordedPulseScene::update(){
    
    
    for (int i = 0; i < 50; i++){
        if (ofRandom(0,1) > 0.8){
            if (val[i] == 0) val[i] = 255;
            else val[i] = 0;
        }
    }
    
    
}

void recordedPulseScene::draw(){
    
    for (int i = 0; i < 50; i++){
        ofSetColor(val[i]);
        float width = ofGetWidth() / (float)50;
        ofFill();
        ofRect(width*i, 0, width, ofGetHeight());
    }
    
    ofDrawBitmapStringHighlight("recorded pulse scene", 20, 60);
}