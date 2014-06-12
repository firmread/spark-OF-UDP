//
//  patternScene.cpp
//  of_colorOscSender
//
//  Created by Firm Read on 6/11/14.
//
//

#include "patternScene.h"

void patternScene::setup(){
    rects.clear();
}

void patternScene::update(){
    
    for (int i = 0; i < rects.size(); i++){
        rects[i].animate();
        if(rects[i].alpha < 0.05){
            rects.erase(rects.begin() + i);
        }
    }
    
    
    if (ofRandom(0,1) > 0.8){
        
        rectAnim newOne;
        newOne.rect.x = ofRandom(0, ofGetWidth()-100);
        newOne.rect.y = 0;
        newOne.color1.setHsb( int(ofRandom(ofGetMouseX(),ofGetMouseX()+ 50)) % 255, ofRandom(150,200), 200);
//        newOne.color2.setHsb(ofRandom(100,150), ofRandom(150,200), 200);
        newOne.color = newOne.color1;
        newOne.color2.set(255);
        newOne.rect.width = ofRandom(5,15);
        newOne.rect.height = ofGetHeight();
        newOne.alpha = 255;
        rects.push_back(newOne);
    }
    decayRate = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0.98, 0.1);
    expandRate = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0.1, 10.0);
    

}


void patternScene::draw(){
    
    ofSetColor(0);
    ofFill();
    ofRect(0,0,ofGetWidth(), ofGetHeight());
    
    for (int i = 0; i < rects.size(); i++){
        rects[i].draw();
    }
    
    ofDrawBitmapStringHighlight("pattern scene\nalpha decay rate (dragged y) : " + ofToString(decayRate) +
                                "\nrect expansion rate (dragged x) : " + ofToString(expandRate), 20, 60);
}

void patternScene::mouseDragged(int x, int y, int button){
    for (int i =0 ; i< rects.size(); i++) {
        rects[i].alphaDecayRate = decayRate;
        rects[i].rectExpansionRate = expandRate;
    }
}