//
//  animation01.h
//  of_colorOscSender
//
//  Created by Firm Read on 6/11/14.
//
//



#pragma once

#include "baseScene.h"

class animation01 : public baseScene{
public:
    void setup();
    void update();
    void draw();
    
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    vector<ofRectangle> rect;
    ofPoint mousePos;
    
};