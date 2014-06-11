#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxOsc.h"
#include "ofxBlur.h"

class colorSender {
    
public: 
    void readXMLdata();
    
    void setup();
    void send();
    void grabScreen();
    void drawSentColors();
    
    
    ofxBlur blur;
    ofFbo   screenTextue;
    ofFbo   lineTexture;
    ofPixels pix;
    
    void drawWherePickingFrom();
    
    string ipAddress;
    int port;
    ofxXmlSettings settings;
    ofxOscSender sender;
    vector < ofColor > colors;
    ofImage centerOfScreen;
};