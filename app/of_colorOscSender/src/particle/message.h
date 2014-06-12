//
//  message.h
//  of_colorOscSender
//
//  Created by Firm Read on 6/12/14.
//
//
#pragma once
#include "ofMain.h"


class message{
public:
    
    
    void draw(){
        ofFill();
        ofSetColor(color);
        ofRect(position, 0, width, ofGetHeight());
    }
    
    void drawPulsy(float sine){
        ofSetColor(color * sine);
        ofRect(position, 0, width, ofGetHeight());
    }
    
    ofColor color;
    float position;
    float speed;
    float width;
};

//typedef struct {
//
//    ofColor color;
//    float position;
//    float speed;
//    float width;
//
//} message;