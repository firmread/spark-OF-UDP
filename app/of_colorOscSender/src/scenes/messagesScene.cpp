//
//  messagesScene.cpp
//  of_colorOscSender
//
//  Created by zach on 6/4/14.
//
//

#include "messagesScene.h"



    
void messagesScene::setup(){
    
    messages.clear();
    
}

void messagesScene::update(){
    
    
    for (int i = 0; i < messages.size(); i++){
        messages[i].position += messages[i].speed;
    }
    
    if ( ofRandom(0,1) > 0.999|| ofGetMousePressed()){
        message m;
        m.width = ofRandom(20,40);
        m.position = -m.width;
        m.speed = ofRandom(0.3, 0.5);
        m.color.set(ofRandom(200,255),ofRandom(0,70),ofRandom(0,70));
        messages.push_back(m);
    }
    
    
    
}

void messagesScene::draw(){
    
    ofClear(0);
    ofFill();
    ofSetColor(0);
    ofRect(0,0,ofGetWidth(), ofGetHeight());
    for (int i = 0; i < messages.size(); i++){
        ofFill();
        ofSetColor(messages[i].color);
        ofRect(messages[i].position, 0, messages[i].width, ofGetHeight());
    }
    
    ofDrawBitmapStringHighlight("messages scene\nclick to generate message", 20, 60);
}
    

