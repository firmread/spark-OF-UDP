
#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class baseScene {
    
public:
    
    ofxGuiGroup gui;
    float blurness;
    
    baseScene(){}
    
    virtual void setup(){
        blurness = 0;
    };
    virtual void update(){};
    virtual void draw(){};
    
    virtual void mouseMoved(int x, int y ){}
    virtual void mouseDragged(int x, int y, int button){}
    virtual void mousePressed(int x, int y, int button){}
    virtual void mouseReleased(int x, int y, int button){}
    
    
    void hide(){
        
    }
    
    void show(){
        
    }
    
};




typedef struct {
    
    ofColor color;
    float position;
    float speed;
    float width;
    
} message;


