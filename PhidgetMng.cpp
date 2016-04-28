//
//  PhidgetMng.cpp
//  PhidgetTest
//
//  Created by dustinshasho on 7/11/14.
//  Copyright (c) 2014 dustinshasho. All rights reserved.
//

#include "PhidgetMng.h"
#include <unistd.h>
#include <algorithm>

PhidgetMng::PhidgetMng(){
    
    for(int i =0; i < DEVICES; i ++)
        _phidgetIds[i]=0;

}
PhidgetMng::~PhidgetMng(){

}

int PhidgetMng :: connect(){
    
    CPhidgetManagerHandle MAN = 0;
    
    CPhidgetManager_create(&MAN);
    
    CPhidgetManager_open(MAN);
    
    sleep(1);

    display_devices(MAN);
    
    return 0;
}

int PhidgetMng:: display_devices(CPhidgetManagerHandle man){

   
    
    // Retrieve the list of attached Phidgets from the manager
    CPhidgetManager_getAttachedDevices((CPhidgetManagerHandle)man, &_phidgetList, &_phidgetCount);

    int serialNumber;
    const char *name;

    // Iterate over the returned Phidget data and save them to var _ids
    int i;
    for (i = 0; i < _phidgetCount; i++) {
        CPhidget_getDeviceName(_phidgetList[i], &name);
        CPhidget_getSerialNumber(_phidgetList[i], &serialNumber);
        printf("%s, %d\n", name, serialNumber);
        // Store name and serial number into a persistent variable
        _phidgetIds[i] = serialNumber;
        
    }
    std::sort(_phidgetIds, _phidgetIds +DEVICES);
    
    // Use the Phidget API to free the memory in the phidgetList Array
    CPhidgetManager_freeAttachedDevicesArray(_phidgetList);
    // Close the manager
    return 0;
}

int PhidgetMng::getPhidgetCount(){

    return _phidgetCount;
}

const int * PhidgetMng :: getPhidgetIds(){

    return _phidgetIds;
    
}









