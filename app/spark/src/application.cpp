#include "application.h"
#include "spark_disable_cloud.h"
#include "pwm.h"
#include "communicationDefines.h"
#include "communicationTypes.h"
#include <math.h>

#define USE_SERIAL

#ifdef USE_SERIAL
    //#define PRINT_IP_ON_CONNECTION
#endif 


unsigned int localPort      = SPARKY_INCOMING_PORT;
unsigned int outgoingPort   = SPARKY_OUTGOING_PORT;
const int INCOMING_PACKET_SIZE = sizeof(ofToSparkyPacket);
const int OUTGOING_PACKET_SIZE = sizeof(sparkyToOFPacket);
byte  packetBufferIncoming[INCOMING_PACKET_SIZE];
byte  packetBufferOutgoing[OUTGOING_PACKET_SIZE];
UDP Udp;


bool bOnline;       // are we online for real?

ofToSparkyPacket O2Spacket;
sparkyToOFPacket S2Opacket;


// function declaration:
void handlePacket( byte * data);
void loopOnline();
void loopOffline();

int r, g, b;

struct color {
    int r, g, b;
};

color previousColor, targetColor;
int targetTime, transitionTime;

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
void setup(){
    // we do very little network related or print out here, since this runs even before we are actually online
    
#ifdef USE_SERIAL
    Serial.begin(9600);
#endif
    
    pwmSetup();
    
    r = 50;
    g = 50;
    b = 50;
    
    targetColor.r = 50;
    targetColor.g = 50;
    targetColor.b = 50;
    
    delay(5);
}

//--------------------------------------------------------------
void loop(){
    
    outOfOrderPerSecondSmooth = 0.95 * outOfOrderPerSecondSmooth + 0.05 * outOfOrderPerSecond;
    missedPacketPerSecondSmooth = 0.95 * outOfOrderPerSecondSmooth + 0.05 * missedPacketPerSecond;
    packetFpsSmooth = 0.95 * packetFpsSmooth + 0.05 * packetFps;
    

    

    //----------------------- are we online for real?
    
    if ((targetColor.r != r)||(targetColor.g != g)||(targetColor.b != b)) {
        if (millis() > targetTime || transitionTime == 0) {
            r = targetColor.r;
            g = targetColor.g;
            b = targetColor.b;
        } else {
            float timeFrame = (targetTime - millis());
            float phase = 1 - (timeFrame)/(float)transitionTime;
            float easingFunc = pow(phase, 2) / (pow(phase,2) + pow(1 - phase, 2));
            // setting up r,g,b with easing func:
            r = previousColor.r + (int)((float)targetColor.r - (float)previousColor.r) * easingFunc;
            g = previousColor.g + (int)((float)targetColor.g - (float)previousColor.g) * easingFunc;
            b = previousColor.b + (int)((float)targetColor.b - (float)previousColor.b) * easingFunc;
        }
    }

    pwm (r,g,b);
    
    bool bOnlinePrev = bOnline;
    
    IPAddress addr = Network.localIP();
    
    if  (addr[0] == 0 && addr[1] == 0 && addr[2] == 0 && addr[3] == 0){
        bOnline = false;
    } else {
        bOnline = true;
    }
    

    

    if (bOnline == true && bOnlinePrev == false){
        Udp.begin(localPort);
    } else if (bOnline == false && bOnlinePrev == true){
        Udp.stop();
    }
    
    //----------------------- do some different stuff:
    if (bOnline){
        loopOnline();
    } else {
        loopOffline();
    }
    
    #ifdef PRINT_IP_ON_CONNECTION
    if (bOnline == false && online == true){
        Serial.println(".");
        Serial.println(addr[0]);
        Serial.println(addr[1]);
        Serial.println(addr[2]);
        Serial.println(addr[3]);
    }
    #endif

    calculateFPS();
    
    
}


//--------------------------------------------------------------
void loopOnline(){
    
    #ifdef USE_SERIAL
        Serial.println(packetFps);
    #endif
    
    
    if (int nbytes = Udp.parsePacket()) {
 
        
        if (nbytes != INCOMING_PACKET_SIZE){
            
            if (nbytes % INCOMING_PACKET_SIZE == 0){
                
               
                int nPackets =  nbytes / INCOMING_PACKET_SIZE;
//                 Serial.println("multipacket");
//                Serial.println(nPackets);
                for (int i = 0; i < nPackets; i++){
                    Udp.read(packetBufferIncoming, INCOMING_PACKET_SIZE);
                    handlePacket(packetBufferIncoming);
                }
            }
            
            
        
        } else {
            
            memset(packetBufferIncoming, 0, INCOMING_PACKET_SIZE);
            
            // todo does read return a value, should we error check?
            
            Udp.read(packetBufferIncoming,nbytes);
            handlePacket(packetBufferIncoming);
            
//            digitalWrite(D7,HIGH);
//            delay(20);
//            digitalWrite(D7,LOW);
        }
    }
}

//--------------------------------------------------------------
void loopOffline(){
    
    delay(5);   // small delay?
    
}

//--------------------------------------------------------------
void handlePacket( byte * data){
    
    
    calculateFPSGotPacket();
    
    // todo: error checking?
    

    // handle O->S packet
    
    // clear memory, copy bytes into struct...
    memset(&O2Spacket, 0, INCOMING_PACKET_SIZE);
    memcpy(&O2Spacket, data, INCOMING_PACKET_SIZE);

    // parse out return IP address
    // O2Spacket.serverIp[]
    IPAddress serverIp;
    serverIp[0] = O2Spacket.ofIp >> 24 & 0xFF;
    serverIp[1] = O2Spacket.ofIp >> 16 & 0xFF;
    serverIp[2] = O2Spacket.ofIp >> 8 & 0xFF;
    serverIp[3] = O2Spacket.ofIp & 0xFF;
    
    
    int packetCount = O2Spacket.packetCount;
    
    if (packetCount < lastPacketReceived){
        packetOutOfOrderCount++;
    } else if ( packetCount - lastPacketReceived != 1){
        packetMissedCount += (packetCount - lastPacketReceived);
    }
    lastPacketReceived = packetCount;
    
    

    // if it's a discovery or heartbeat packet, return something
    if (O2Spacket.packetType == PACKET_TYPE_DISCOVERY || O2Spacket.packetType == PACKET_TYPE_HEARTBEAT){
        
        // send packet back
        // how long have we been running
        S2Opacket.millisRunning = millis();
        // return the OF time from this packet
        S2Opacket.ofPacketSentOutTime = O2Spacket.ofPacketSentOutTime;
        // grab our own IP address and put it in the packet
        IPAddress addr = Network.localIP();
        unsigned char a = addr[0];
        unsigned char b = addr[1];
        unsigned char c = addr[2];
        unsigned char d = addr[3];
        int addressAsInt = a << 24 | b << 16 | c << 8 | d;
        S2Opacket.ipSpark = addressAsInt;
        
        S2Opacket.sparkDataFrameRate = packetFpsSmooth;
        S2Opacket.outOfOrderPerSecond = outOfOrderPerSecondSmooth;
        S2Opacket.missedPacketPerSecond = missedPacketPerSecondSmooth;
        
        // MAC ADDRESS ?
        
        // gray our ID (uuid)
        String uuidTemp = Spark.deviceID();
        // memcpy packet into byte array:
        memcpy(S2Opacket.uuid,uuidTemp.c_str(),uuidTemp.length());
        // send packet
        Udp.beginPacket(serverIp, outgoingPort);
        memcpy(packetBufferOutgoing, &S2Opacket, OUTGOING_PACKET_SIZE);
        Udp.write(packetBufferOutgoing, OUTGOING_PACKET_SIZE);
        Udp.endPacket();
        

      
        
    } else if (O2Spacket.packetType == PACKET_TYPE_COLOR){
        
        // don't respond, right?
        
        if ((O2Spacket.r != targetColor.r)||(O2Spacket.g != targetColor.g)||(O2Spacket.b != targetColor.b)) {
            
            if (O2Spacket.transitionTime != 0){
            
                previousColor.r = r;
                previousColor.g = g;
                previousColor.b = b;
                //
                targetColor.r = O2Spacket.r;
                targetColor.g = O2Spacket.g;
                targetColor.b = O2Spacket.b;

                // defaulting transition to second
                transitionTime = O2Spacket.transitionTime;

                targetTime = millis() + transitionTime;
            } else {
                previousColor.r = O2Spacket.r;
                previousColor.g = O2Spacket.g;
                previousColor.b = O2Spacket.b;
                //
                targetColor.r = O2Spacket.r;
                targetColor.g = O2Spacket.g;
                targetColor.b = O2Spacket.b;
                
                r =O2Spacket.r;
                g =O2Spacket.g;
                b =O2Spacket.b;
                
                
                transitionTime = 0;
                
                targetTime = millis();
                
            }
        }
        
    }
}



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

