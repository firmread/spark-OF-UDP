
#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "message.h"
#include "simpleParticle.h"
#include "particle.h"
#include "rectAnim.h"

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
    
    virtual void keyPressed(int key){};
    virtual void keyReleased(int key){};
    
    void hide(){
        
    }
    
    void show(){
        
    }
    
};





