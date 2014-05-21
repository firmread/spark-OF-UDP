//OF send out to spark
typedef struct {
    float time;
    int frameNumber;
//    float random;
//    float r;
    
} packet;



//spark send back to OF
typedef struct {
    long millisRunning;
} returnPacket;
