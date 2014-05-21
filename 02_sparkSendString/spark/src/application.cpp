#include "application.h"
#include "spark_disable_cloud.h"

// local port to listen on
// unsigned int localPort = 8888;
unsigned int outgoingPort = 7777;
int led = D7;

// const int PACKET_SIZE = 12;
// byte  packetBuffer[PACKET_SIZE]; 
UDP Udp;
IPAddress ip(192, 168, 2, 24);

void setup()
{
  pinMode(led, OUTPUT);
  // start the UDP
  // Udp.begin(outgoingPort);
  Serial.begin(9600);
  
  
  Serial.println(Network.localIP());
  Serial.println(Network.subnetMask());
  Serial.println(Network.gatewayIP());
  Serial.println(Network.SSID());
}

void loop()
{

        Udp.begin(outgoingPort);
            Udp.beginPacket(ip, outgoingPort);
            Udp.write("hello spark here");
            Udp.endPacket();

        Udp.stop();
        delay(1);
    
}

