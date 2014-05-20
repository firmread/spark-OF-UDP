#include "application.h"
#include "spark_disable_cloud.h"

// local port to listen on
unsigned int localPort = 8888;
int led = D7;

const int PACKET_SIZE = 12;
byte  packetBuffer[PACKET_SIZE];

unsigned long lastsec;
int delaysec = 100;
int counter=0;

// An UDP instance to let us send and receive packets over UDP
UDP Udp;

void setup()
{
    pinMode(led, OUTPUT);
    // start the UDP
    Udp.begin(localPort);
    Serial.begin(9600);
    
    
    Serial.println(Network.localIP());
    Serial.println(Network.subnetMask());
    Serial.println(Network.gatewayIP());
    Serial.println(Network.SSID());
}

void loop()
{
    
    // Serial.println("i saw sparks");
    
    int packetSize = Udp.parsePacket();
    if(packetSize)
    {
        digitalWrite(led, HIGH);   // Turn ON the LED
        delay(200);               // Wait for 1000mS = 1 second
        digitalWrite(led, LOW);    // Turn OFF the LED
        delay(200);               // Wait for 1 second
        
        Udp.read(packetBuffer,PACKET_SIZE);
        IPAddress remote = Udp.remoteIP();
        
        Serial.println((char *)packetBuffer);
        Serial.print("packetSize = ");
        Serial.println(packetSize);
    }
    
    
    // unsigned long nowsec = millis();
    // if (nowsec >= (lastsec + delaysec)) {
    //     lastsec = nowsec;
    
    //     if (int nbytes = Udp.parsePacket()) {
    //         Udp.read(packetBuffer,nbytes);
    //         for(int i=0;i<nbytes;i++) {
    //             char c = (char)packetBuffer[i];
    //             Serial.print(c);
    //             // Serial.print(c>>4,HEX);
    //             // Serial.print(c&0x0f,HEX);
    //         }
    //         Serial.println();
    //         Serial.println(Udp.remoteIP());
    //     }
    //     Udp.stop();
    //     delay(1);
    //     Udp.begin(localPort);
    
    // }
    
}