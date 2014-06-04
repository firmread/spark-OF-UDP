//-------------------------------------------------------------------------------
// for calculating packet frame rate
int frameCount = 0;
int currentTime = 0;
int previousTime = 0;
float packetFps = 0;
int lastPacketReceived = 0;
int packetOutOfOrderCount = 0;
int packetMissedCount = 0;
float outOfOrderPerSecond = 0;
float missedPacketPerSecond = 0;
float outOfOrderPerSecondSmooth = 0;
float missedPacketPerSecondSmooth = 0;
float packetFpsSmooth = 0;


//--------------------------------------------------------------
void statsGotPacket(){
    frameCount++;
}

void statsLookAtPacketOrder( int newPacketNum ){
	if (newPacketNum <= lastPacketReceived){
        newPacketNum++;
    } else if ( newPacketNum - lastPacketReceived != 1){
        packetMissedCount += (newPacketNum - lastPacketReceived);
    }
    lastPacketReceived = newPacketNum;
}

void statsUpdate(){
	outOfOrderPerSecondSmooth = 0.95 * outOfOrderPerSecondSmooth + 0.05 * outOfOrderPerSecond;
    missedPacketPerSecondSmooth = 0.95 * outOfOrderPerSecondSmooth + 0.05 * missedPacketPerSecond;
    packetFpsSmooth = 0.95 * packetFpsSmooth + 0.05 * packetFps;
}

//--------------------------------------------------------------

void statsCalculateFPS(){

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

