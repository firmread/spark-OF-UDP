//
//  movieScene.cpp
//  of_colorOscSender
//
//  Created by Firm Read on 6/11/14.
//
//

#include "movieScene.h"


void movieScene::setup(){
    
    player.loadMovie("mov6_x264_b.mp4");
    player.play();
    player.setSpeed(0.25);
}

void movieScene::update(){
    
    player.update();
}

void movieScene::draw(){
    
    ofSetColor(255,255,255);
    player.draw(0,0,ofGetWidth(), ofGetHeight());
}