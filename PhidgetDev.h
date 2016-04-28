//
//  PhidgetDev.h
//  PhidgetTest
//
//  Created by dustinshasho on 7/11/14.
//  Copyright (c) 2014 dustinshasho. All rights reserved.
//

#ifndef __PhidgetTest__PhidgetDev__
#define __PhidgetTest__PhidgetDev__

#include <phidget21/phidget21.h>
#include <iostream>

#define DEVICES 4

const int OVERLAP = 40;
const int SAMPLESIZE = 120;
const int WINDOWS = 60;



class PhidgetSpatial{

public:

    PhidgetSpatial();
    ~PhidgetSpatial();
       /** \brief Closes and deletes device.
         *
         * \param device CphidgetInterfaceKitHandle a IFK handle
         * \return void
         *
         */
    void DestroyDevice(CPhidgetSpatialHandle device);
    int connect(const int * devNum);
    int readPhidget();
    void getAccelXYZ();
    void collectSample();
    void print();
    
    friend std::ostream& operator << (std::ostream &outStream, const PhidgetSpatial &aWindow);
    
    private:
    
    struct AccelVector {
        
        double x;
        double y;
        double z;
    };
    
    struct Window{
        
        AccelVector xyzDevices [SAMPLESIZE][DEVICES];
        
        
    };
    


    void readPhidgetAccel();
    AccelVector * getWindow();
    AccelVector _devAccel[DEVICES];                //accel vector for each device
    AccelVector _windowOverlap[OVERLAP][DEVICES]; //overlap window
    Window _windowAccel;                          // a full window with overlap
    Window _dataSet[WINDOWS];
    CPhidgetSpatialHandle _SPAT[DEVICES];         //handle for each device
    
 
};

#endif /* defined(__PhidgetTest__PhidgetDev__) */
