





typedef struct {
    unsigned char packetType;       // 0 = discovery 1=heartbear  2=
    float time;
    unsigned char r;
    unsigned char g;
    unsigned char b;
} ofToSparkyPacket;



//spark send back to OF
typedef struct {
    unsigned long millisRunning;
    int ip;
    unsigned char uuid[24];
    
} sparkyToOFPacket;
