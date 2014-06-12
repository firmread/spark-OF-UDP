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

//    blur.setup(ofGetWidth(), ofGetHeight());
//    fboA.allocate(ofGetWidth(), ofGetHeight());
//    fboB.allocate(ofGetWidth(), ofGetHeight());
    speed = 5.0;
    phase = 0.4;
}

void pulseScene::update(){
    
    
    
    
    
}

void pulseScene::draw(){
    
    ofClear(0);
  
    float width = ofGetWidth() / 50.0;
    
    for (int i = 0; i < 50; i++){
        
        float color = sin(ofGetElapsedTimef() * speed/5.0 + (i*phase));
        color = ofMap(color, -1, 1, 0.0, 1.0);
        
        ofColor temp;
        temp.setHsb( (int)(ofGetElapsedTimef() * 0.1 + i * 5) % 255, 255, color*255);
        
        ofSetColor( temp);
        ofFill();
        ofRect(i*width, 0, width, ofGetHeight());
        
    }
    
    ofDrawBitmapStringHighlight("pulse scene\nspeed (dragged x) : " + ofToString(speed)+
                                "\nphase (dragged y) : " + ofToString(phase), 20, 60);
    
    
}

void pulseScene::mouseDragged(int x, int y,int button){
    speed = ofMap(x, 0, ofGetWidth(), 1.0, 100.0);
    phase = ofMap(y, 0, ofGetHeight(), 0.01, 2.0);
}
    

