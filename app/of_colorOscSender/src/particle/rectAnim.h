//
//  rectAnim.h
//  of_colorOscSender
//
//  Created by Firm Read on 6/12/14.
//
//


//typedef struct {
//    float alpha;
//    ofColor color;
//    ofColor color2;
//    
//    ofRectangle rect;
//    
//} rectAnim;

class rectAnim {
public:
    
    float alpha;
    ofColor color1;
    ofColor color2;
    
    ofColor color;

    ofRectangle rect;
    float alphaDecayRate = 0.98;
    float rectExpansionRate = 1.0;
    
    void animate(){
        alpha *= alphaDecayRate;
        float transit = ofMap(alpha, 0, 255, 0,1.0);
        color = (color1*transit + color2*(1-transit))/2;
        rect.width += 2*rectExpansionRate;
        rect.x -= 1*rectExpansionRate;
    }
    
    void draw(){
        
        ofSetColor(color, alpha);
        ofRect(rect);
    }
};