//-------------------------------------------------------------------------------
// for calculating packet frame rate
int frameCount = 0;
int currentTime = 0;
int previousTime = 0;
float packetFps = 0;
void calculateFPSGotPacket();
void calculateFPS();

// for calculating packet ordering issues
int lastPacketReceived = 0;
int packetOutOfOrderCount = 0;
int packetMissedCount = 0;
float outOfOrderPerSecond = 0;
float missedPacketPerSecond = 0;

float outOfOrderPerSecondSmooth = 0;
float missedPacketPerSecondSmooth = 0;
float packetFpsSmooth = 0;




//--------------------------------------------------------------
void calculateFPSGotPacket(){
    frameCount++;
}
//--------------------------------------------------------------

void calculateFPS(){

    currentTime = millis();

    //  Calculate time passed
    int timeInterval = currentTime - previousTime;
    

    if(timeInterval > 1000){
        //  calculate the number of frames per second
        packetFps = frameCount / (float)(timeInterval / 1000.0);
        
        Serial.println(packetFps);
    
        outOfOrderPerSecond = packetOutOfOrderCount / (float)(timeInterval / 1000.0);
        missedPacketPerSecond = packetMissedCount / (float)(timeInterval / 1000.0);
    
        //  Set time
        previousTime = currentTime;
    
        //  Reset frame count
        packetOutOfOrderCount = 0;
        packetMissedCount = 0;
        frameCount = 0;
    }
}
//-------------------------------------------------------------------------------

