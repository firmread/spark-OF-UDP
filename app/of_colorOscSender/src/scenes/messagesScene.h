

#include "baseScene.h"

#pragma once

//#include "ofxBlur.h"


class messagesScene : public baseScene {
    
    void setup();
    void update();
    void draw();
    
    vector < message > messages;
    
//    ofxBlur blur;
//    ofFbo fboA;
//    ofFbo fboB;
    
    
    
};
