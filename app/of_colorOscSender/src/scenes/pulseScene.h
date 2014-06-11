

#include "baseScene.h"

#pragma once

#include "ofxBlur.h"


class pulseScene : public baseScene {
    
    void setup();
    void update();
    void draw();
    
   
    
    ofxBlur blur;
    ofFbo fboA;
    ofFbo fboB;
    
    
    
};
