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
    
    sineSpeed = 0.2;
    minColor = 0.5;
    colorVaryRange = 20;
    colorVarySpeed = 0.1;
    speedMultiplier = 1;
    
}

void collidingMessageScene::update(){
    
    
    for (int i = 0; i < messagesL.size(); i++){
        messagesL[i].position += messagesL[i].speed * speedMultiplier;
    }
    
    for (int i = 0; i < messagesR.size(); i++){
        messagesR[i].position -= messagesR[i].speed * speedMultiplier;
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
    
    
    sort(messagesL.begin(), messagesL.end(), comparisonFunction);
    sort(messagesR.begin(), messagesR.end(), comparisonFunctionInverse);
    
//    for (int i = 0; i < messagesL.size(); i++){
//        for (int j = 0; j < messagesR.size(); j++) {
//            if (i != messagesL.begin() && j != messagesR.begin() ) {
//                <#statements#>
//            }
    if (messagesL.size() != 0 && messagesR.size() != 0) {
            if (abs(messagesL[0].position - messagesR[0].position) < messagesL[0].width ) {
                messagesL.erase(messagesL.begin());
                messagesR.erase(messagesR.begin());
                //create another bang
            }
//        }
//    }
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
    speedMultiplier = ofMap(x, 0, ofGetWidth(), 0.5, 2.0);
}


//void collidingMessageScene::detectCollision(message &a, message &b){
//    if (abs(a.position - b.position) < a.width ) {
//        
//    }
//}