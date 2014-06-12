#pragma once

#include "ofMain.h"
#include "colorSender.h"

#include "baseScene.h"
#include "messagesScene.h"
#include "pulseScene.h"
#include "crazyScene.h"
#include "movieScene.h"
#include "patternScene.h"
#include "recordedPulseScene.h"
#include "particleScene.h"
#include "ballScene.h"
#include "collidingMessageScene.h"


#include "ofxGui.h"
#include "ofxBlur.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        vector < baseScene * > scenes;
    
    
        colorSender sender;
    
        float pos;
        ofxBlur blur;
        float blurness;
    bool bHoldingReturn;
        bool bHitReturnFlash;
        float flashAlpha;
    bool bFadeAlpha;
    
};
