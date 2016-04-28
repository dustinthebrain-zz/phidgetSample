//
//  PhidgetDev.cpp
//  PhidgetTest
//
//  Created by dustinshasho on 7/11/14.
//  Copyright (c) 2014 dustinshasho. All rights reserved.
//

#include "PhidgetDev.h"
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <fstream>

PhidgetSpatial ::PhidgetSpatial(){
    
    int i;
    int j;
    
    for (i=0; i <DEVICES; i++){
        _SPAT[i] =0;
        
    }

    for (i=0; i<OVERLAP; i++){ // overlap from previous sample
        for (j=0; j <DEVICES; j++){
            _windowOverlap[i][j].x = 0;
            _windowOverlap[i][j].y = 0;
            _windowOverlap[i][j].z = 0;
        }
    }

}
PhidgetSpatial ::~PhidgetSpatial(){

}

void PhidgetSpatial :: DestroyDevice(CPhidgetSpatialHandle device){

    CPhidget_close((CPhidgetHandle)&device);
    CPhidget_delete((CPhidgetHandle)&device);
}

int PhidgetSpatial :: connect(const int * devNum){
    
    int i;
    
    std :: cout << devNum[0]<<std::endl;
    std :: cout << devNum[1]<<std::endl;
    std :: cout << devNum[2]<<std::endl;
    std :: cout << devNum[3]<<std::endl;
    for (i=0; i <DEVICES; i++){
        CPhidgetSpatial_create(&_SPAT[i]);
        CPhidget_open((CPhidgetHandle)_SPAT[i], devNum[i]);
        sleep(1);
    }
    
    return 0;
}


void PhidgetSpatial ::readPhidgetAccel(){
    //gather accelration data
    int i;
    for (i=0; i <DEVICES; i++){
        CPhidgetSpatial_getAcceleration(_SPAT[i], 0, &_devAccel[i].x);
        CPhidgetSpatial_getAcceleration(_SPAT[i], 1, &_devAccel[i].y);
        CPhidgetSpatial_getAcceleration(_SPAT[i], 2, &_devAccel[i].z);
    }
    
}


void PhidgetSpatial :: collectSample(){
    int i;
    int j;
    int k;
    time_t timer;
   
    
    time(&timer);
    std::cout << timer<<std::endl;
    for (k = 0; k < WINDOWS; k++){
    //LOOP 1
        for (i=0; i<OVERLAP; i++){ // overlap from previous sample
            for (j=0; j <DEVICES; j++){
                _windowAccel.xyzDevices[i][j].x = _windowOverlap[i][j].x;
                _windowAccel.xyzDevices[i][j].y = _windowOverlap[i][j].y;
                _windowAccel.xyzDevices[i][j].z = _windowOverlap[i][j].z;
            }
            usleep(16666);
        }
    
    //LOOP 2
        for (i=OVERLAP; i<SAMPLESIZE-OVERLAP; i++){ // collect new sample data (part 1)
            for (j=0; j <DEVICES; j++){
                CPhidgetSpatial_getAcceleration(_SPAT[j], 0, &_windowAccel.xyzDevices[i][j].x);
                CPhidgetSpatial_getAcceleration(_SPAT[j], 1, &_windowAccel.xyzDevices[i][j].y);
                CPhidgetSpatial_getAcceleration(_SPAT[j], 2, &_windowAccel.xyzDevices[i][j].z);
            }
            usleep(16666);
        }
    
    //LOOP 3
        for (i=SAMPLESIZE-OVERLAP; i<SAMPLESIZE; i++){ // (part 2) continue collecting new sample data and record the overlap
            for (j=0; j <DEVICES; j++){
                CPhidgetSpatial_getAcceleration(_SPAT[j], 0, &_windowAccel.xyzDevices[i][j].x);
                _windowOverlap[i-(SAMPLESIZE-OVERLAP)][j].x = _windowAccel.xyzDevices[i][j].x;
                CPhidgetSpatial_getAcceleration(_SPAT[j], 1, &_windowAccel.xyzDevices[i][j].y);
                _windowOverlap[i-(SAMPLESIZE-OVERLAP)][j].y = _windowAccel.xyzDevices[i][j].y;
                CPhidgetSpatial_getAcceleration(_SPAT[j], 2, &_windowAccel.xyzDevices[i][j].z);
                _windowOverlap[i-(SAMPLESIZE-OVERLAP)][j].z = _windowAccel.xyzDevices[i][j].z;
            }
            usleep(16666);
        }

        _dataSet[k] = _windowAccel;
    }
    time(&timer);
    std::cout << timer<<std::endl;
}



void PhidgetSpatial ::getAccelXYZ(){

    //int i;
    //int j;
    
    collectSample();
    
    /*
    
    for (i=0; i<SAMPLESIZE; i++){
        for (j=0; j <DEVICES; j++){
            //readPhidgetAccel();
            std :: cout << "DEVICE: "<<j<<std::endl;
            std :: cout << _windowAccel.xyzDevices[i][j].x<<",";
            std :: cout << _windowAccel.xyzDevices[i][j].y<<",";
            std :: cout << _windowAccel.xyzDevices[i][j].z<<std::endl;
        }
    }
    usleep (1000000);
    std :: cout << "NEW SAMPLE _________"<<std::endl;*/
}


void PhidgetSpatial::print(){

    int i;
    int j;
    int k;
    
    std::ofstream fout;
    
    fout.open("/Users/Dustin/Desktop/357_Ortho/raw/walking_60_120_40_dustin_1.txt");
    if (fout.fail()){
        
        std::cout << "could not open file";
    }
    
  
    for (i =0; i < WINDOWS; i ++)
        for (j = 0; j < SAMPLESIZE; j++)
            for (k=0; k < DEVICES; k++){
                fout << _dataSet[i].xyzDevices[j][k].x<<","<< _dataSet[i].xyzDevices[j][k].y<<","<< _dataSet[i].xyzDevices[j][k].z;
                if (k == (DEVICES -1)){
                    fout <<"\n";
                }
                else{
                    fout <<",";
                }
            }
    
  /*  for (i =0; i < WINDOWS; i ++)
        for (j = 0; j < SAMPLESIZE; j++)
            for (k=0; k < DEVICES; k++){
                std::cout << _dataSet[i].xyzDevices[j][k].x<<","<< _dataSet[i].xyzDevices[j][k].y<<","<< _dataSet[i].xyzDevices[j][k].z<<",";
                if (k == (DEVICES -1)){
                    std::cout <<"class2\n";
                }
                  sleep(.5);
            }
  */
    
    
    fout.close();
    
}