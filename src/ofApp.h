#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxSimpleSerial.h"

class ofApp : public ofBaseApp{
    
public:
    
    //  serial communication
    ofxSimpleSerial serial;
    string message;
    string pressMess;   //  this is the string value coming in from arduino
    int pressInt;       //  we will convert the string to an int
    
    void setup();
    void update();
    void draw();
    bool requestRead;
    
    void onNewMessage(string & message);
    
    ofxBox2d                                 box2d;
    vector     <shared_ptr<ofxBox2dCircle> > circles;

};