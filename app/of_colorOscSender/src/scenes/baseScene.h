
#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class baseScene {
    
public:
    
    ofxGuiGroup gui;
    
    baseScene(){}
    
    virtual void setup(){};
    virtual void update(){};
    virtual void draw(){};
    
    void hide(){
        
    }
    
    void show(){
        
    }
};


class crazyScene : public baseScene {


    void draw(){
        
        
        if (ofGetFrameNum() % 20 < 10){
            ofSetColor( ofRandom(200,255), ofRandom(200,255), ofRandom(200,255));
            ofFill();
            ofRect(0,0,ofGetWidth(), ofGetHeight());
        
        } else {
            ofSetColor(0);
            ofFill();
            ofRect(0,0,ofGetWidth(), ofGetHeight());
        }
    }
};


typedef struct {
    float alpha;
    ofColor color;
    ofColor color2;
    
    ofRectangle rect;
    
} rectAnim;


class patternScene : public baseScene {
    
public:
    
    vector < rectAnim > rects;
    
    void setup(){
        
    }
    
    void update(){
        
        for (int i = 0; i < rects.size(); i++){
            rects[i].alpha *= 0.98;
            
            rects[i].rect.width += 2*1.0;
            rects[i].rect.x -= 1*1.0;
        }
        
        
        if (ofRandom(0,1) > 0.8){
            
            rectAnim newOne;
            newOne.rect.x = ofRandom(0, ofGetWidth()-100);
            newOne.rect.y = 0;
            newOne.color.setHsb(ofRandom(ofGetMouseX(),ofGetMouseX()+ 50), ofRandom(150,200), 200);
            newOne.color2.setHsb(ofRandom(100,150), ofRandom(150,200), 200);
            newOne.rect.width = ofRandom(5,15);
            newOne.rect.height = ofGetHeight();
            newOne.alpha = 255;
            rects.push_back(newOne);
        }
    }
    
    void draw(){
        
        ofSetColor(0);
        ofFill();
        ofRect(0,0,ofGetWidth(), ofGetHeight());
        
        for (int i = 0; i < rects.size(); i++){
            ofSetColor(rects[i].color.r,rects[i].color.g,rects[i].color.b, rects[i].alpha);
            ofRect(rects[i].rect);
        }
        
    }
    
};

class movieScene : public baseScene {
    
    ofVideoPlayer player;
    
    void setup(){
        player.loadMovie("mov6_x264_b.mp4");
        player.play();
        player.setSpeed(0.25);
    }
    
    void update(){
        
        player.update();
    }
    void draw(){
        
        ofSetColor(255,255,255);
        player.draw(0,0,ofGetWidth(), ofGetHeight());
    }
    
    
};






class recordedPulseScene : public baseScene {
    
    
    int val[50];
    
    void setup(){
        
        for (int i = 0; i < 50; i++){
            val[i] = 0;
        }
    }
    
    void update(){
        
        
        for (int i = 0; i < 50; i++){
            if (ofRandom(0,1) > 0.8){
                if (val[i] == 0) val[i] = 255;
                else val[i] = 0;
            }
        }
       
    }
    void draw(){
       
        for (int i = 0; i < 50; i++){
            ofSetColor(val[i]);
            float width = ofGetWidth() / (float)50;
            ofFill();
            ofRect(width*i, 0, width, ofGetHeight());
        }
        
        
        
    }
    
    
};

