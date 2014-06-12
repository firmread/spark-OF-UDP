//
//  messagesScene.cpp
//  of_colorOscSender
//
//  Created by zach on 6/4/14.
//
//

#include "collidingMessageScene.h"




void collidingMessageScene::setup(){
    
    //vector < message > messages;
    
    //    blur.setup(ofGetWidth(), ofGetHeight());
    //    fboA.allocate(ofGetWidth(), ofGetHeight());
    //    fboB.allocate(ofGetWidth(), ofGetHeight());
    
    
}

void collidingMessageScene::update(){
    
    
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

void collidingMessageScene::draw(){
    
    //blur.begin();
    ofClear(0);
    //ofSetColor(255);
    //fboA.draw(0, 0);
    ofFill();
    ofSetColor(0);
    ofRect(0,0,ofGetWidth(), ofGetHeight());
    for (int i = 0; i < messages.size(); i++){
        ofFill();
        ofSetColor((messages[i].color)* abs(sin(ofGetElapsedTimef()*messages[i].width/5) + 1)/2);
        ofRect(messages[i].position, 0, messages[i].width, ofGetHeight());
    }
    //blur.end();
    
    
    //    fboA.begin();
    //    ofSetColor(255);
    //    blur.draw();
    //    fboA.end();
    //
    //    blur.draw();
}


