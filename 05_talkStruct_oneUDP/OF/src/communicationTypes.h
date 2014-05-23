//OF send out to spark
typedef struct {
//    unsigned char packetType;       // 0 = whoareyou 1=heartbear  2=
    float time;
    unsigned char r;
    unsigned char g;
    unsigned char b;
} packet;



//spark send back to OF
typedef struct {
    unsigned long millisRunning;
    int ip;
    unsigned char uuid[24];
    
} returnPacket;
