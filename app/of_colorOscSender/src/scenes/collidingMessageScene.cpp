//
//  messagesScene.cpp
//  of_colorOscSender
//
//  Created by zach on 6/4/14.
//
//

#include "collidingMessageScene.h"


bool comparisonFunction(  message a, message b ) {
    return a.position > b.position;
}

bool comparisonFunctionInverse ( message a, message b ) {
    return a.position < b.position;
}

void collidingMessageScene::setup(){
    
    messagesL.clear();
    messagesR.clear();
    rects.clear();
    
    sineSpeed = 0.2;
    minColor = 0.5;
    colorVaryRange = 20;
    colorVarySpeed = 0.1;
    speedMultiplier = 1;
    
}

void collidingMessageScene::update(){
    
    
    for (int i = 0; i < messagesL.size(); i++){
        messagesL[i].position += messagesL[i].speed * speedMultiplier;
        if (messagesL[i].position > ofGetWidth()){
            messagesL.erase(messagesL.begin() + i);
        }
    }
    
    for (int i = 0; i < messagesR.size(); i++){
        messagesR[i].position -= messagesR[i].speed * speedMultiplier;
        if (messagesR[i].position < -messagesR[i].width) {
            messagesR.erase(messagesR.begin() + i);
        }
    }
    
    
    for (int i = 0 ; i < rects.size(); i++) {
        rects[i].animate();
    }
    
//    if ( ofRandom(0,1) > 0.999|| ofGetMousePressed()){
//        message m;
//        m.width = ofRandom(20,40);
//        m.position = -m.width;
//        m.speed = ofRandom(0.3, 0.5);
// //        m.color.set(ofRandom(200,255),ofRandom(0,70),ofRandom(0,70));
//        float colorGenTimeSine = sin(ofGetElapsedTimef()* colorVarySpeed);
//        colorGenTimeSine = ofMap(colorGenTimeSine, -1, 1, colorVaryRange, 255-colorVaryRange);
//        colorGenTimeSine += ofRandom(-colorVaryRange,colorVaryRange);
//        m.color.setHsb(colorGenTimeSine, ofRandom(200,255), ofRandom(200,255));
//        messagesL.push_back(m);
//    }
    
    //sort vectors
    sort(messagesL.begin(), messagesL.end(), comparisonFunction);
    sort(messagesR.begin(), messagesR.end(), comparisonFunctionInverse);
    
    // check the closest ones
    if (messagesL.size() != 0 && messagesR.size() != 0) {
        if (abs(messagesL[0].position - messagesR[0].position) < messagesL[0].width ) {
            //create another bang
            rectAnim newOne;
            newOne.rect.x = messagesR[0].position;
            newOne.rect.y = 0;
            
            if (messagesL[0].width > messagesR[0].width) {
                newOne.color1 = messagesL[0].color;
            }
            else{
                newOne.color1 = messagesR[0].color;
            }
            
            newOne.color = newOne.color1;
            newOne.color2.set(255);
            newOne.rect.width = ofRandom(5,15);
            newOne.rect.height = ofGetHeight();
            newOne.alpha = 255;
            rects.push_back(newOne);
            
            messagesL.erase(messagesL.begin());
            messagesR.erase(messagesR.begin());
        }
    }

    
}

void collidingMessageScene::draw(){
    
    ofClear(0);
    ofFill();
    ofBackground(0);
    for (int i = 0; i < messagesL.size(); i++){
        float sine = sin(ofGetElapsedTimef() * messagesL[i].width * sineSpeed);
        sine = ofMap(sine, -1, 1, minColor, 1);
        messagesL[i].drawPulsy(sine);
//        messagesL[i].draw();
        
    }
    
    for (int i = 0; i < messagesR.size(); i++){
        float sine = sin(ofGetElapsedTimef() * messagesR[i].width * sineSpeed);
        sine = ofMap(sine, -1, 1, minColor, 1);
        messagesR[i].drawPulsy(sine);
//        messagesR[i].draw();
        
    }
    // draw collision rect
    for (int i = 0; i < rects.size(); i++){
        rects[i].draw();
    }

    
    ofDrawBitmapStringHighlight("colliding message scene\npress A and S\ndrag mouseX to adjust speed", 20, 60);
}



void collidingMessageScene::keyPressed(int key){
    if (key == 'a'){
        message m;
        m.width = ofRandom(20,40);
        m.position = -m.width;
        m.speed = ofRandom(0.3, 0.5);
        float colorGenTimeSine = sin(ofGetElapsedTimef()* colorVarySpeed);
        colorGenTimeSine = ofMap(colorGenTimeSine, -1, 1, colorVaryRange, 255-colorVaryRange);
        colorGenTimeSine += ofRandom(-colorVaryRange,colorVaryRange);
        m.color.setHsb(colorGenTimeSine, ofRandom(200,255), ofRandom(200,255));
        messagesL.push_back(m);
        
    }
    
    if (key == 's'){
        message m;
        m.width = ofRandom(20,40);
        m.position = ofGetWidth();
        m.speed = ofRandom(0.3, 0.5);
        float colorGenTimeSine = sin(ofGetElapsedTimef()* colorVarySpeed);
        colorGenTimeSine = ofMap(colorGenTimeSine, 1, -1, colorVaryRange, 255-colorVaryRange);
        colorGenTimeSine += ofRandom(-colorVaryRange,colorVaryRange);
        m.color.setHsb(colorGenTimeSine, ofRandom(200,255), ofRandom(200,255));
        messagesR.push_back(m);

    }
}


void collidingMessageScene::mouseDragged(int x , int y , int button){
    speedMultiplier = ofMap(x, 0, ofGetWidth(), 0.5, 50.0);
}


//void collidingMessageScene::detectCollision(message &a, message &b){
//    if (abs(a.position - b.position) < a.width ) {
//        
//    }
//}