//
//  messagesScene.cpp
//  of_colorOscSender
//
//  Created by zach on 6/4/14.
//
//

#include "pulseScene.h"



    
void pulseScene::setup(){
    
    //vector < message > messages;
    
    blur.setup(ofGetWidth(), ofGetHeight());
    fboA.allocate(ofGetWidth(), ofGetHeight());
    fboB.allocate(ofGetWidth(), ofGetHeight());
    
    
}

void pulseScene::update(){
    
    
    
    
    
}

void pulseScene::draw(){
    
    ofClear(0);
  
    float width = ofGetWidth() / 50.0;
    
    for (int i = 0; i < 50; i++){
        
        float color = sin(ofGetElapsedTimef() * 5/5.0 + (i*0.4)) * 0.5 + 0.5;
        
        ofColor temp;
        temp.setHsb( (int)(ofGetElapsedTimef()*0.1*255 + i * 5) % 255, 255, color*255);
        
        ofSetColor( temp);
        ofFill();
        ofRect(i*width, 0, width, ofGetHeight());
        
    }
    
    
    
}
    

