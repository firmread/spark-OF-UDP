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
    speed = 0.25;
    player.setSpeed(speed);
}

void movieScene::update(){
    
    player.update();
}

void movieScene::draw(){
    
    ofSetColor(255,255,255);
    player.draw(0,0,ofGetWidth(), ofGetHeight());
    
    ofDrawBitmapStringHighlight("movie scene\nclick to increse speed\nspeed : " +
                                ofToString(speed), 20, 60);
}


void movieScene::mousePressed(int x, int y, int button){
    speed = player.getSpeed()+ 0.75;
    if (player.getSpeed() > 10.0){
        speed = 0.25;
    }
        player.setSpeed(speed);
//    player.setSpeed(0.25);
}