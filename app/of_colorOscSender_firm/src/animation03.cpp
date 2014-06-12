//
//  animation03.cpp
//  of_colorOscSender
//
//  Created by Firm Read on 6/11/14.
//
//

#include "animation03.h"

void animation03::setup(){
    
    ofRectangle temp;
    for (int i = 0; i < ofGetWidth()/10 + 1; i++){
        temp.set(i*10, 0, 10, ofGetHeight());
        rect.push_back(temp);
        
    }
}

//--------------------------------------------------------------
void animation03::update(){
    
    for (int i = 0; i < ofGetWidth()/10 + 1; i++){
        rect[i].x++;
        if (rect[i].x > ofGetWidth()+10) {
            rect[i].x = -10;
        }
    }

}

//--------------------------------------------------------------
void animation03::draw(){
    
    for (int i = 0; i < ofGetWidth()/10 + 1; i++){
        ofPushStyle();
        ofColor color;
        color.setHsb(i*20%255, 255, 255);
        ofSetColor(color);
        ofRect(rect[i]);
        ofPopStyle();
    }
    
    //    ofFill();
    //    ofSetColor(255,255,255);
    //    img.draw(pos, 0); //(mouseX,0,500,500);
    //    ofDisableAlphaBlending();
    
    
    
    ofPushStyle();
    ofSetColor(ofColor::salmon);
    ofRect(mousePos.x, mousePos.y, 100, 100);
    ofPopStyle();
}

//--------------------------------------------------------------
void animation03::mouseMoved(int x, int y ){
    mousePos.set(x, y);
}

//--------------------------------------------------------------
void animation03::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void animation03::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void animation03::mouseReleased(int x, int y, int button){
    
}

