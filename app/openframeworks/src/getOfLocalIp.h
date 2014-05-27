//
//  getOfLocalIp.h
//  mainApp
//
//  Created by Firm Read on 5/27/14.
//
//

#ifndef mainApp_getOfLocalIp_h
#define mainApp_getOfLocalIp_h

#include "ofMain.h"


class getOfLocalIp{
    

public:
    vector <string> allIp;
    string localIp;
    
    //--------------------------------------------------------------
    
    getOfLocalIp(){
        string execReturn = exec("ifconfig | grep -E \"inet ([0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3})\" | awk \'{print $2}\'");
        
        allIp = ofSplitString(execReturn, "\n");
    }
    
    //--------------------------------------------------------------
    
    //find out my ip through this cmd!
    std::string exec(const char* cmd) {
        
        FILE* pipe = popen(cmd, "r");
        if (!pipe) return "ERROR";
        char buffer[128];
        std::string result = "";
        while(!feof(pipe)) {
            
            if(fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
        
        pclose(pipe);
        return result;
        
    }

    
    //--------------------------------------------------------------
    
    void parse(){
    // parsing works,, not sure if it would works in every case tho
        for (int i=0; i<allIp.size(); i++) {
            vector <string> ipBreakdown = ofSplitString(allIp[i],".");
            if (ipBreakdown[0] == "192") {
                localIp = allIp[i];
                break;
            }
            else if (ipBreakdown[0]!= "127") {
                localIp = allIp[i];
                break;
            }
        }
    }
    
    //--------------------------------------------------------------
    string getString(){
        parse();
        return localIp;
    }
    
    //--------------------------------------------------------------
    
    int getInt(){
        parse();
        vector<string> ipBreakdown = ofSplitString(localIp, ".");
        
        unsigned char a = ofToInt(ipBreakdown[0]);
        unsigned char b = ofToInt(ipBreakdown[1]);
        unsigned char c = ofToInt(ipBreakdown[2]);
        unsigned char d = ofToInt(ipBreakdown[3]);
        
        int addressAsInt = a << 24 | b << 16 | c << 8 | d;
        
        return addressAsInt;

    }

};

#endif
