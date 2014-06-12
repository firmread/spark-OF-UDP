

#include "baseScene.h"

#pragma once

//#include "ofxBlur.h"


class patternScene : public baseScene {

    
public:
    
    vector < rectAnim > rects;
    
    void setup();
    void update();
    void draw();
    
    void mouseDragged(int x, int y, int button);
    
    float decayRate;
    float expandRate;
};
