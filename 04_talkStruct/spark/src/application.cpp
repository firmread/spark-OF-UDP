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
int led = D0;

const int PACKET_SIZE = 12;
byte  packetBuffer[PACKET_SIZE]; 

// unsigned long lastsec;
// int delaysec = 100;

// An UDP instance to let us send and receive packets over UDP
UDP Udp, UdpOut;

// IPAddress ip(192, 168, 2, 24);

timer t, t2;






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

  t.setup(100);
  t2.setup(100);
}

void loop()
{

  Serial.println(millis());
    // check the device variable sizeof
    // Serial.println(sizeof(int));
    // Serial.println(sizeof(float));
    // Serial.println(millis());

  t.update(millis());

  if (t.bTimerFired()){
      // cout << "timer! " << ofGetElapsedTimef() << endl;     

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

        Udp.flush();

        UdpOut.beginPacket(Udp.remoteIP(), outgoingPort);

        char buffer [50];
        int n=sprintf (buffer, "%lu", millis());

        UdpOut.write("I've been running for " );
        UdpOut.write(buffer);
        UdpOut.write(" milliseconds");
        UdpOut.endPacket();

        UdpOut.stop();
        delay(1);
        UdpOut.begin(outgoingPort);
        
        Udp.stop();
        delay(1);
        Udp.begin(localPort);
//

      }

    }
  }

  // t2.update(millis());
  // if (t2.bTimerFired()){
  //   Serial.println("restarting!");
   
  //   Udp.flush();

   

  // }

  delay(5);


}


