

#include "colorSender.h"
#include "ofxBlur.h"

void colorSender::readXMLdata(){
    ofxXmlSettings settings;
    settings.load("settings.xml");
    ipAddress   = settings.getValue("ipAddress", "");
    port        = settings.getValue("port", 0);
}

void colorSender::setup(){
    readXMLdata();
    sender.setup(ipAddress, port);
    colors.assign(50, ofColor::pink);
    
    screenTextue.allocate(ofGetWidth(), 1);
    lineTexture.allocate(50,1);
    pix.allocate(50,1,OF_PIXELS_RGBA);

    //int radius = 32, float shape = .2
    blur.setup(ofGetWidth(), 1, 16);
    
}

void colorSender::grabScreen(){
    
    screenTextue.getTextureReference().loadScreenData(0, ofGetHeight()/2, ofGetWidth(), 1);
    //
    ofSetColor(255,255,255);
    
    
    blur.begin();
    ofClear(0);
    screenTextue.draw(0,0);
    blur.end();
    
    lineTexture.begin();
    blur.base.draw(0,0,50,1);
    lineTexture.end();
   
    lineTexture.readToPixels(pix);
    
    for (int i = 0; i < colors.size(); i++){
        colors[i] = pix.getColor(i,0);
        
        
//        colors[i].r = powf(colors[i].r/255.0, 2.0) * 255;
//        colors[i].g = powf(colors[i].g/255.0, 2.0) * 255;
//        colors[i].b = powf(colors[i].b/255.0, 2.0) * 255;
//        
        
        
        colors[i].a = 255;
    }
    
}

void colorSender::drawWherePickingFrom(){
    
    
    ofNoFill();
    ofSetColor(255,255,255);
    ofRect(0, ofGetHeight()/2, ofGetWidth(), 1);
    ofFill();
    ofSetColor(0,0,0, 20);
    ofRect(0, ofGetHeight()/2, ofGetWidth(), 1);
    
}


void colorSender::send(){
    
    ofxOscMessage m;
    m.setAddress("/color");
    for (int i = 0; i < 50; i++){
        int colorAsInt = colors[i].r << 24 | colors[i].g << 16 | colors[i].b << 8;
        m.addIntArg(colorAsInt);
    }
    sender.sendMessage(m);
}

void colorSender::drawSentColors(){
    // ------- draw colors at the base of the window
    float width = ofGetWidth() / (float)colors.size();
    for (int i = 0; i < colors.size(); i++){


        ofSetColor(colors[i]);
        ofFill();
        ofRect(i*width, ofGetHeight(), width-1, -30);

        if (colors[i].getBrightness() < 10){
            // white outline
            ofSetColor(ofColor::white);
            ofNoFill();
            ofRect(i*width, ofGetHeight(), width-1, -30);
        } else {
            // black outline
            ofSetColor(ofColor::black);
            ofNoFill();
            ofRect(i*width, ofGetHeight(), width-1, -30);
        }
        
    }
}