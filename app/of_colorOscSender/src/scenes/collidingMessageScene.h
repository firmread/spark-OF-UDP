

#include "baseScene.h"

#pragma once

//#include "ofxBlur.h"


//typedef struct {
//    
//    ofColor color;
//    float position;
//    float speed;
//    float width;
//    
//} message;

class collidingMessageScene : public baseScene {
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    
    vector < message > messagesL;
    vector < message > messagesR;
    
    float sineSpeed;
    float minColor; // 0-1
    float colorVaryRange;
    float colorVarySpeed;
    float speedMultiplier;
    
//    void detectCollision(message &a, message &b);
    
};
