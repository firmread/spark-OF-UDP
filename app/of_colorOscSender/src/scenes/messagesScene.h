

#include "baseScene.h"

#pragma once

#include "ofxBlur.h"


typedef struct {
    
    ofColor color;
    float position;
    float speed;
    float width;
    
} message;

class messagesScene : public baseScene {
    
    void setup();
    void update();
    void draw();
    
    vector < message > messages;
    
    ofxBlur blur;
    ofFbo fboA;
    ofFbo fboB;
    
    
    
};
