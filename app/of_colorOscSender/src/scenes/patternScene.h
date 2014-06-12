

#include "baseScene.h"

#pragma once

//#include "ofxBlur.h"


class patternScene : public baseScene {
    
    
    
typedef struct {
    float alpha;
    ofColor color;
    ofColor color2;
    
    ofRectangle rect;
    
} rectAnim;
    

    
public:
    
    vector < rectAnim > rects;
    
    void setup();
    
    void update();
    
    void draw();
    
};
