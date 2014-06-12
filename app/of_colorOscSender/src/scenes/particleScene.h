
#pragma once
#include "baseScene.h"

class particleScene : public baseScene {
    
    
    void setup();
    
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void mouseDragged(int x, int y, int button);

    
    vector <particle> particles;
    };
