#include "application.h"
#include "spark_disable_cloud.h"



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

//packet structs
typedef struct {
  float time;
  int frameNumber;    
} packet;







// local port to listen on
unsigned int localPort = 8888;
unsigned int outgoingPort = 7777;
int led1 = D0;
int led2 = D1;
int led3 = D2;

const int PACKET_SIZE = 12;
byte  packetBuffer[PACKET_SIZE]; 

// An UDP instance to let us send and receive packets over UDP
UDP Udp;
timer t;






void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  // start the UDP
  Udp.begin(localPort); 

  Serial.begin(9600);
  
  
  Serial.println(Network.localIP());
  Serial.println(Network.subnetMask());
  Serial.println(Network.gatewayIP());
  Serial.println(Network.SSID());

  t.setup(100);

}

void loop()
{
  digitalWrite(led1, HIGH);
  Serial.println(millis());
    // check the device variable sizeof
    // Serial.println(sizeof(int));
    // Serial.println(sizeof(float));
    // Serial.println(millis());

  t.update(millis());

  if (t.bTimerFired()){  

    digitalWrite(led1, LOW);
    if (int nbytes = Udp.parsePacket()) {
      
      if (nbytes != sizeof(packet)){
        Serial.println("bad packet ???");
        Udp.flush();

      } else {

        memset(packetBuffer, 0, sizeof(packet));

        Udp.read(packetBuffer,nbytes);

        for(int i=0;i<nbytes;i++) {
          char c = (char)packetBuffer[i];
                // Serial.print(c);

                // Serial.print(c>>4,HEX);
                // Serial.print(c&0x0f,HEX);
        }

        packet p;
        memset(&p, 0, sizeof(packet));
        memcpy(&p, packetBuffer, sizeof(packet));

        Serial.print(Udp.remoteIP());
        Serial.print(" : time = ");
        Serial.print(p.time);
        Serial.print(" : nFrame = ");
        Serial.println(p.frameNumber);

        // Udp.flush();
        // Udp.stop();

        // delay(1);

        // Udp.begin(outgoingPort);
        // Udp.beginPacket(Udp.remoteIP(), outgoingPort);

        // char buffer [50];
        // int n=sprintf (buffer, "%lu", millis());

        // Udp.write("I've been running for " );
        // Udp.write(buffer);
        // Udp.write(" milliseconds");
        // Udp.endPacket();

        // Udp.flush();
        // Udp.stop();

        // delay(1);
        // Udp.begin(localPort);




        Udp.flush();

        Udp.stop();
        delay(1);
        Udp.begin(outgoingPort);

        Udp.beginPacket(Udp.remoteIP(), outgoingPort);

        char buffer [50];
        int n=sprintf (buffer, "%lu", millis());

        Udp.write("I've been running for " );
        Udp.write(buffer);
        Udp.write(" milliseconds");
        Udp.endPacket();

        
        Udp.stop();
        delay(1);
        Udp.begin(localPort);
        
      }
    }
  }


   

  // }

  delay(5);

}


