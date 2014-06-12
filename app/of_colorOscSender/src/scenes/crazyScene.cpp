//
//  crazyScene.cpp
//  of_colorOscSender
//
//  Created by Firm Read on 6/11/14.
//
//

#include "crazyScene.h"

void crazyScene::setup(){}
    
    
void crazyScene::update(){}


void crazyScene::draw(){
    
    
    if (ofGetFrameNum() % 20 < 10){
        ofSetColor( ofRandom(200,255), ofRandom(200,255), ofRandom(200,255));
        ofFill();
        ofRect(0,0,ofGetWidth(), ofGetHeight());
        
    } else {
        ofSetColor(0);
        ofFill();
        ofRect(0,0,ofGetWidth(), ofGetHeight());
    }
}