//
//  animation01.cpp
//  of_colorOscSender
//
//  Created by Firm Read on 6/11/14.
//
//

#include "animation01.h"

void animation01::setup(){
    
    ofRectangle temp;
    for (int i = 0; i < ofGetWidth()/10 + 1; i++){
        temp.set(i*10, 0, 10, ofGetHeight());
        rect.push_back(temp);
        
    }
}

//--------------------------------------------------------------
void animation01::update(){
    
    for (int i = 0; i < ofGetWidth()/10 + 1; i++){
        rect[i].x++;
        if (rect[i].x > ofGetWidth()+10) {
            rect[i].x = -10;
        }
    }

}

//--------------------------------------------------------------
void animation01::draw(){
    
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
void animation01::mouseMoved(int x, int y ){
    mousePos.set(x, y);
}

//--------------------------------------------------------------
void animation01::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void animation01::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void animation01::mouseReleased(int x, int y, int button){
    
}

