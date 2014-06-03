#pragma once

#include "ofMain.h"



inline string ipFromInt ( int ipInt ) {

    int ip[4];
    ip[0] = ipInt >> 24 & 0xFF;
    ip[1] = ipInt >> 16 & 0xFF;
    ip[2] = ipInt >> 8 & 0xFF;
    ip[3] = ipInt & 0xFF;
    
    string result = ofToString(ip[0]) + "." + ofToString(ip[1]) + "."
    + ofToString(ip[2]) + "." + ofToString(ip[3]);
    
    //cout << result << endl;
    
    return result;
    
}

inline string uuidFromCharArray( unsigned char uuid[24] ){
    string temp( uuid, uuid + (24) / sizeof uuid[0] );
    return temp;
}

