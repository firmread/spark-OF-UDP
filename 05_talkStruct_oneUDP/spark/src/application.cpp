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





//OF send out to spark
typedef struct {
    float time;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    
} packet;



//spark send back to OF
typedef struct {
    unsigned long millisRunning;
    int ip;

    // string uuid;
    //unsigned int deviceID;
    // unsigned char deviceID[12];
    // byte macAddress[6];
    unsigned char uuid[24];

} returnPacket;







// local port to listen on
unsigned int localPort = 8888;
unsigned int outgoingPort = 7777;
int led = D0;

const int PACKET_SIZE = 12;
byte  packetBuffer[PACKET_SIZE]; 

// An UDP instance to let us send and receive packets over UDP
UDP Udp;

// IPAddress ip(192, 168, 2, 24);
timer t, t2;






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

  t.setup(100);
  t2.setup(100);
}

void loop()
{

  // unsigned char temp[8];
  // IPAddress tempIP = Network.localIP();
  // memset(temp, 0, 8);
  // memcpy(temp, &tempIP, 8);
  // Serial.println(temp);
  // Serial.println(ID1);
  // int temp;
  // memset(&temp,0, )
  // memcpy()
// Serial.println(Network.macAddress());
  // Serial.println(Spark.deviceID());
  t.update(millis());

  if (t.bTimerFired()){ 

    if (int nbytes = Udp.parsePacket()) {
      
      if (nbytes != sizeof(packet)){
        Serial.println("bad packet ???");
      } else {

        memset(packetBuffer, 0, sizeof(packet));
        
        Udp.read(packetBuffer,nbytes);


        packet p;
        memset(&p, 0, sizeof(packet));
        memcpy(&p, packetBuffer, sizeof(packet));

        Serial.print(Udp.remoteIP());
        Serial.print("r: ");
        Serial.print(p.r);
        Serial.print("g: ");
        Serial.print(p.g);
        Serial.print("b: ");
        Serial.print(p.b);
        Serial.print("time: ");
        Serial.println(p.time);


        returnPacket rp;
        //time
        rp.millisRunning = millis();
        //ip
        IPAddress addr = Network.localIP();
        unsigned char a = addr[0];
        unsigned char b = addr[1];
        unsigned char c = addr[2];
        unsigned char d = addr[3];
        int addressAsInt = a << 24 | b << 16 | c << 8 | d;
        rp.ip = addressAsInt;
        //id
        String uuidTemp = Spark.deviceID();
        memcpy(rp.uuid,uuidTemp.c_str(),uuidTemp.length());

        Udp.beginPacket(Udp.remoteIP(), outgoingPort);


        unsigned char packetBytes[sizeof(returnPacket)];
        memcpy(packetBytes, &rp, sizeof(returnPacket));

        Udp.write(packetBytes,sizeof(returnPacket));
        Udp.endPacket();

      }

    }
  }

  t2.update(millis());
  if (t2.bTimerFired()){
    Serial.println("restarting!");
    Udp.stop();
    delay(1);
    Udp.begin(localPort);

   

  }

  delay(5);


}


