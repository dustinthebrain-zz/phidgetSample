//
//  main.cpp
//  PDC_accel
//
//  Created by dustinshasho on 10/23/14.
//  Copyright (c) 2014 dustinshasho. All rights reserved.
//

#include <iostream>
#include <string>
#include "PhidgetMng.h"
#include "PhidgetDev.h"


int main(int argc, const char * argv[])
{
    const int * iDs;// storage for device ids
    std::string trash;
    

    PhidgetMng manager; //create manager object
    PhidgetSpatial devices; //create spatial device object
    
    manager.connect(); //run phidget manager
    
    iDs = manager.getPhidgetIds(); //retrive device Ids from manager
    
    devices.connect(iDs); //open all devices found
    
    std :: cout << "press any key to continue...";
    getline(std::cin,trash);
    

    devices.collectSample();
    
    
    std:: cout <<"press any key to print...";
    getline(std::cin,trash);
    devices.print();
    
    std::cout <<"files done!\n";
    
    return 0;
}

