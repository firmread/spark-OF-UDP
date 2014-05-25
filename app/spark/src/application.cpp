#include "application.h"
#include "spark_disable_cloud.h"

#include "communicationDefines.h"
#include "communicationTypes.h"


unsigned int localPort      = SPARKY_INCOMING_PORT;
unsigned int outgoingPort   = SPARKY_OUTGOING_PORT;
int led                     = D0;


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


//--------------------------------------------------------------
void setup(){
    // we do very little network related or print out here, since this runs even before we are actually online
    pinMode(led, OUTPUT);
    Serial.begin(9600);
    
}

//--------------------------------------------------------------
void loop(){

    //----------------------- are we online for real?
    
    bool bOnlinePrev = bOnline;
    
    IPAddress addr = Network.localIP();
    
    if  (addr[0] == 0 && addr[1] == 0 && addr[2] == 0 && addr[3] == 0){
        bOnline = false;
    } else {
        bOnline = true;
    }
    
    if (bOnline == true && bOnlinePrev == false){
        Udp.begin(localPort);
    }
    
    //----------------------- do some different stuff:
    if (bOnline){
        loopOnline();
    } else {
        loopOffline();
    }
}


//--------------------------------------------------------------
void loopOnline(){
    
    if (int nbytes = Udp.parsePacket()) {
    
        if (nbytes != INCOMING_PACKET_SIZE){
            
            // TODO handle this
            
            Serial.println("bad packet ???");
        
        } else {
            
            memset(packetBufferIncoming, 0, INCOMING_PACKET_SIZE);
            
            // todo does read return a value, should we error check?
            
            Udp.read(packetBufferIncoming,nbytes);
            handlePacket(packetBufferIncoming);
            
        }
    }
}

//--------------------------------------------------------------
void loopOffline(){
    
    delay(5);   // small delay?
    
}

//--------------------------------------------------------------
void handlePacket( byte * data){
    
    
    // todo: error checking?
    

    // handle O->S packet
    
    memset(&O2Spacket, 0, INCOMING_PACKET_SIZE);
    memcpy(&O2Spacket, data, INCOMING_PACKET_SIZE);
    
    Serial.print(Udp.remoteIP());
    Serial.print("r: ");
    Serial.print(O2Spacket.r);
    Serial.print("g: ");
    Serial.print(O2Spacket.g);
    Serial.print("b: ");
    Serial.print(O2Spacket.b);
    Serial.print("time: ");
    Serial.println(O2Spacket.time);
    
    // S->O packet
    
    S2Opacket.millisRunning = millis();
    IPAddress addr = Network.localIP();
    unsigned char a = addr[0];
    unsigned char b = addr[1];
    unsigned char c = addr[2];
    unsigned char d = addr[3];
    int addressAsInt = a << 24 | b << 16 | c << 8 | d;
    S2Opacket.ip = addressAsInt;
    String uuidTemp = Spark.deviceID();
    memcpy(S2Opacket.uuid,uuidTemp.c_str(),uuidTemp.length());
    Udp.beginPacket(Udp.remoteIP(), outgoingPort);

    memcpy(packetBufferOutgoing, &S2Opacket, OUTGOING_PACKET_SIZE);
    
    Udp.write(packetBufferOutgoing, OUTGOING_PACKET_SIZE);
    Udp.endPacket();
    
    
    
    
}