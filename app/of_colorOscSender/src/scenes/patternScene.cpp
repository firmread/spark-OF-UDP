//
//  patternScene.cpp
//  of_colorOscSender
//
//  Created by Firm Read on 6/11/14.
//
//

#include "patternScene.h"

void patternScene::setup(){
    
}

void patternScene::update(){
    
    for (int i = 0; i < rects.size(); i++){
        rects[i].alpha *= 0.98;
        
        rects[i].rect.width += 2*1.0;
        rects[i].rect.x -= 1*1.0;
    }
    
    
    if (ofRandom(0,1) > 0.8){
        
        rectAnim newOne;
        newOne.rect.x = ofRandom(0, ofGetWidth()-100);
        newOne.rect.y = 0;
        newOne.color.setHsb(ofRandom(ofGetMouseX(),ofGetMouseX()+ 50), ofRandom(150,200), 200);
        newOne.color2.setHsb(ofRandom(100,150), ofRandom(150,200), 200);
        newOne.rect.width = ofRandom(5,15);
        newOne.rect.height = ofGetHeight();
        newOne.alpha = 255;
        rects.push_back(newOne);
    }

}


void patternScene::draw(){
    
    ofSetColor(0);
    ofFill();
    ofRect(0,0,ofGetWidth(), ofGetHeight());
    
    for (int i = 0; i < rects.size(); i++){
        ofSetColor(rects[i].color.r,rects[i].color.g,rects[i].color.b, rects[i].alpha);
        ofRect(rects[i].rect);
    }
}