

#include "baseScene.h"
#pragma once

//#include "ofxBlur.h"



class ballScene : public baseScene {
    
    
    
    void setup();
    void update();
    void draw();
    void mouseDragged(int x, int y, int button);
    void mouseMoved(int x, int y);
    
    vector <simpleParticle> sp;
    
    ofPoint mousePos;
    float sineAlphaSpeed;
    float minAlpha;
};
