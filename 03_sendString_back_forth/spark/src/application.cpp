#include "application.h"
#include "spark_disable_cloud.h"

// local port to listen on
unsigned int localPort = 8888;
unsigned int outgoingPort = 7777;
int led = D7;

const int PACKET_SIZE = 12;
byte  packetBuffer[PACKET_SIZE]; 

unsigned long lastsec;
int delaysec = 100;

// An UDP instance to let us send and receive packets over UDP
UDP Udp, UdpOut;
// UDP UdpOut;


IPAddress ip(192, 168, 2, 24);

void setup()
{
  pinMode(led, OUTPUT);
  // start the UDP
  Udp.begin(localPort);
  UdpOut.begin(outgoingPort);

  Serial.begin(9600);
  
  
  Serial.println(Network.localIP());
  Serial.println(Network.subnetMask());
  Serial.println(Network.gatewayIP());
  Serial.println(Network.SSID());
}

void loop()
{
    
    unsigned long nowsec = millis();
    if (nowsec >= (lastsec + delaysec)) {
        lastsec = nowsec;


        if (int nbytes = Udp.parsePacket()) {
            Udp.read(packetBuffer,nbytes);
            for(int i=0;i<nbytes;i++) {
                char c = (char)packetBuffer[i];
                Serial.print(c);
                // Serial.print(c>>4,HEX);
                // Serial.print(c&0x0f,HEX);
            }
            Serial.println();
            Serial.println(Udp.remoteIP());



            UdpOut.beginPacket(Udp.remoteIP(), outgoingPort);
            UdpOut.write("hello");
            UdpOut.endPacket();

            UdpOut.stop();     
            delay(1);
            UdpOut.begin(outgoingPort);
            
        }
        Udp.stop();
        delay(1);
        Udp.begin(localPort);

    }



    
}

