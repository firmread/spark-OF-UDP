
#pragma once

typedef struct {
    unsigned char packetType;       // 0 = discovery 1=heartbeat  2=color
    float ofPacketSentOutTime;
    int ofIp;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    int transitionTime;             // 0 = instantaneous :) (argument =
    int packetCount;                // each packet will be sent in order.  maybe we can drop packets that are old, etc.
} ofToSparkyPacket;



//spark send back to OF
typedef struct {
    unsigned long millisRunning;
    float ofPacketSentOutTime;
    int ipSpark;
    float sparkDataFrameRate;               // how many packets per second are we getting
    float missedPacketPerSecond;                  // how many times did we get a packet that was not numerically synchronized.
    float outOfOrderPerSecond;              // how many packets came in a wrong order?
    unsigned char uuid[24];
    
} sparkyToOFPacket;
