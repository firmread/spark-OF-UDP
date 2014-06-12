#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxOsc.h"

class colorSender {
    
public: 
    void readXMLdata();
    
    void setup();
    void send();
    void grabScreen();
    void drawSentColors();
//    void blendWithNextPixels(float intensity);
    
    ofFbo   screenTextue;
    ofFbo   lineTexture;
    ofPixels pix;
    
    string ipAddress;
    int port;
    ofxXmlSettings settings;
    ofxOscSender sender;
    vector < ofColor > colors;
    ofImage centerOfScreen;
    
    
};