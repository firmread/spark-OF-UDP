

#include "baseScene.h"
#include "simpleParticle.h"
#pragma once

//#include "ofxBlur.h"



class ballScene : public baseScene {
    
    
    
    void setup();
    void update();
    void draw();
    void mouseDragged(int x, int y, int button);
    
    vector <simpleParticle> sp;
};
