#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //  environment
    ofSetVerticalSync(true);
    ofBackgroundHex(0x000000);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofDisableAntiAliasing();
    
    //  box 2d attributes
    box2d.init();
    box2d.setGravity(0, 77.0);
    box2d.setFPS(60.0);
    box2d.createBounds();
    
    for(int i=0; i<100; i++){
        
        float r = ofRandom(10, 20);
        shared_ptr<ofxBox2dCircle> circle = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
        
        //  setPhysics arguments: density, bounce, friction
        circle.get()->setPhysics(8.0, 0.7, 0.3);
        circle.get()->setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2, r);
        circles.push_back(circle);
        
    }
    
    //  serial setup
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    int baud = 9600;
    serial.setup(1, baud);
    serial.startContinuousRead();
    ofAddListener(serial.NEW_MESSAGE,this,&ofApp::onNewMessage);
    message = "";
}

void ofApp::onNewMessage(string & message){
    
    vector<string> input = ofSplitString(message, " ");
    pressMess = input[0];
    
    pressInt = std::stoi (pressMess);
    
    cout << "pressure: " << pressMess << "\n";
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(requestRead){
        
        cout << "sendRequest\n";
        serial.sendRequest();
        requestRead = false;
    }
    
    //  update the circles & boxes physics
    box2d.update();
    ofVec2f startForce(ofGetWidth()/2, ofGetHeight()/2);
    
    for(int i=0; i<circles.size(); i++){
        circles[i].get()->addAttractionPoint(ofGetWidth()*0.1,ofGetHeight()/2, pressInt/20*0.9);
        circles[i].get()->addAttractionPoint(ofGetWidth()*0.2,ofGetHeight()/2, pressInt/20*0.9);
        circles[i].get()->addAttractionPoint(ofGetWidth()*0.3,ofGetHeight()/2, pressInt/20*0.9);
        circles[i].get()->addAttractionPoint(ofGetWidth()*0.7,ofGetHeight()/2, pressInt/20*0.9);
        circles[i].get()->addAttractionPoint(ofGetWidth()*0.8,ofGetHeight()/2, pressInt/20*0.9);
        circles[i].get()->addAttractionPoint(ofGetWidth()*0.9,ofGetHeight()/2, pressInt/20*0.9);
        
        
//        if you'd like to try this project without the microcontroller uncomment this block and comment out pressInt
        
//        circles[i].get()->addAttractionPoint(ofGetWidth()*0.1,ofGetHeight()/2, mouseY/20*0.9);
//        circles[i].get()->addAttractionPoint(ofGetWidth()*0.2,ofGetHeight()/2, mouseY/20*0.9);
//        circles[i].get()->addAttractionPoint(ofGetWidth()*0.3,ofGetHeight()/2, mouseY/20*0.9);
//        circles[i].get()->addAttractionPoint(ofGetWidth()*0.7,ofGetHeight()/2, mouseY/20*0.9);
//        circles[i].get()->addAttractionPoint(ofGetWidth()*0.8,ofGetHeight()/2, mouseY/20*0.9);
//        circles[i].get()->addAttractionPoint(ofGetWidth()*0.9,ofGetHeight()/2, mouseY/20*0.9);

        circles[i].get()->addRepulsionForce(startForce, 1);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    //  colors
    int colors [ ] = { 0xFFFF1A, 0xFF0000, 0x6C0CE8, 0x0DAAFF, 0xE87B0C, 0x31D11A };
    
    //  draw circles and boxes
    for(int i=0; i<circles.size(); i++) {
        ofFill();
        ofSetHexColor(colors[rand() % 5]);
        circles[i].get()->draw();
    }
    
    box2d.drawGround();
    
    //  message on screen
    string info = "";
    info += "pressure: "+ofToString(pressInt)+"\n";
    ofSetHexColor(0xFFFFFF);
    ofDrawBitmapString(info, 30, 30);
    
}

