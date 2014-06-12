

#include "colorSender.h"


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
    
    screenTextue.allocate(ofGetWidth(), 50);
    lineTexture.allocate(50,1);
    pix.allocate(50,1,OF_PIXELS_RGBA);
    
}

void colorSender::grabScreen(){
    
    screenTextue.getTextureReference().loadScreenData(0, ofGetHeight()/2-25, ofGetWidth(), 50);
    lineTexture.begin();
    ofSetColor(255,255,255);
    screenTextue.draw(0,0,50,1);
    lineTexture.end();
   
    lineTexture.readToPixels(pix);
    
    for (int i = 0; i < colors.size(); i++){
        colors[i] = pix.getColor(i,0);
    }
    
}
//void colorSender::blendWithNextPixels(float intensity){
//    for (int i = 1; i < colors.size()-1; i++){
//        colors[i] = ((( colors[i-1] + colors[i+1] )/2 ) * intensity) + colors[i] * (1 - intensity);
//    }
//}


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
    ofPushStyle();
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
    ofPopStyle();
}