


#include "baseScene.h"

#pragma once

//#include "ofxBlur.h"

class movieScene : public baseScene {
    
    ofVideoPlayer player;
    
    void setup();
    void update();
    void draw();
    
    void mousePressed(int x, int y, int button);
    
    float speed;
};
