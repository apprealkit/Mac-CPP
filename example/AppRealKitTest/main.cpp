//
//  main.cpp
//  AppRealKitTest
//
//  Created by Pham Thai Hoa on 6/8/15.
//  Copyright (c) 2015 apprealkit.com. All rights reserved.
//
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "balancer.h"

using namespace std;

std::string loginID = "1234";
std::string memberID = "5678";

static void receiveMessageCallback(const std::string &sMessage, int iCode) {
    std::cout << "receiveMessage Message:" << sMessage << " and Code:" << iCode << std::endl;
}

static void createRoomCallback(const std::string &sMessage, int iCode) {
    std::cout << "createRoom Message:" << sMessage << " and Code:" << iCode << std::endl;
}

static void authenticateCallback(const std::string &sMessage, int iCode) {
    std::cout << "authenticateCallback Message:" << sMessage << " and Code:" << iCode << std::endl;
    
    //Create ROOM ID
    std::map<std::string, std::string> arrProperties;
    arrProperties["name"] = "ROOM_TEST\n+++\n";
    arrProperties["description"] = "ROOM_DESCRIPTION\n+++\n";
    int iCapacity = 0;
    
    //Create a room without receive the response message
    //AppRealKit::Realtime::Balancer::AsyncCallbackFunc createRoomCallback = NULL;
    AppRealKit::Realtime::Balancer::getInstance()->createRoom(loginID, arrProperties, iCapacity, createRoomCallback);
}

static void openedCallback(const std::string &sMessage, int iCode) {
    std::cout << "Message:" << sMessage << " and Code:" << iCode << std::endl;
    
    //Call authenticate
    AppRealKit::Realtime::Balancer::getInstance()->authenticate(loginID, authenticateCallback);
}

int main(int argc, const char * argv[]) {
    std::string appID_="080693ab-7123-4aee-b560-9f6a8a332a43";
    std::string appSecret_="VORAI5D6yz";
    std::string hostIP_="192.168.10.102";
    int iPort_=7777;
    bool bDebug = true;
    
    //Get balancer instance
    AppRealKit::Realtime::Balancer *oBalancer = AppRealKit::Realtime::Balancer::getInstance();
    
    //Set verbose flag
    oBalancer->setVerbose(bDebug);
    
    //Set product ID
    oBalancer->setProductID(appID_, appSecret_);
    
    //Set all callback here
    oBalancer->onKitOpen(openedCallback);
    oBalancer->onKitMessage(receiveMessageCallback);
    
    //Connect to server
    oBalancer->connect(hostIP_, iPort_);
    
    //Waiting any pressed key
    std::string sInputString;
    std::cin >> sInputString;
    
    //Disconnect
    oBalancer->close();
    AppRealKit::Realtime::Balancer::release();
    
    return 0;
}
