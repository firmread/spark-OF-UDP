
#pragma once


class timer {
    
private:
    int lastFireTime;
    int  millisTimer;
    bool bFiredThisFrame;
    
public:
    void setup( int millisToFire ){
        lastFireTime = 0;
        bFiredThisFrame = false;
        millisTimer = millisToFire;
    }
    
    void update( int currentTimeMillis){
        int elapsedTime = currentTimeMillis - lastFireTime;
        bFiredThisFrame = false;
        if (elapsedTime > millisTimer){
            bFiredThisFrame = true;
            lastFireTime = currentTimeMillis;
        }
    }
    
    bool bTimerFired(){
        return bFiredThisFrame;
    }
    
};
