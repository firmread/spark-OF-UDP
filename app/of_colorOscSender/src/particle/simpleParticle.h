//
//  simpleParticle.h
//  of_colorOscSender
//
//  Created by Firm Read on 6/11/14.
//
//

#include "ofMain.h"



class simpleParticle{
public:
    float x;
    float y;
    float xspeed;
    float yspeed;
    
    ofColor c;

    void setup(){
        
        x = 100;
        y = 100;
        xspeed = 2.5;
        yspeed = 2;
        
    }
    
    void update(){
        
        x = x + xspeed;
        y = y + yspeed;
        
        if ((x > ofGetWidth()) || (x < 0)) {
            xspeed = xspeed * -1;
        }
        if ((y > ofGetHeight()) || (y < 0)) {
            yspeed = yspeed * -1;
        }

    }
    
    void draw(){
        
        ofSetColor(c);
        ofFill();
        ofCircle(x, y, 50);
        

    }
    
    void addAttractionForce(int _x, int _y, float radius, float scale){
        // ----------- (1) make a vector of where this particle p is:
        ofVec2f posOfForce;
        posOfForce.set(_x, _y);
        
        // ----------- (2) calculate the difference & length
        
        ofVec2f diff( x - posOfForce.x, y - posOfForce.y);
        float length	= diff.length();
        
        // ----------- (3) check close enough
        
        bool bAmCloseEnough = true;
        if (radius > 0){
            if (length > radius){
                bAmCloseEnough = false;
            }
        }
        
        // ----------- (4) if so, update force
        
        if (bAmCloseEnough == true){
            float pct = 1 - (length / radius);  // stronger on the inside
            diff.normalize();
            
            x = (x * 0.9) + (_x * 0.1);
            y = (y * 0.9) + (_y * 0.1);
            
//            frc.x = frc.x - diff.x * scale * pct;
//            frc.y = frc.y - diff.y * scale * pct;
//            p.frc.x = p.frc.x + diff.x * scale * pct;
//            p.frc.y = p.frc.y + diff.y * scale * pct;
        }
        
    }
};