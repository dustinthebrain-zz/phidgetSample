//
//  PhidgetMng.h
//  PhidgetTest
//
//  Created by dustinshasho on 7/11/14.
//  Copyright (c) 2014 dustinshasho. All rights reserved.
//

#ifndef __PhidgetTest__PhidgetMng__
#define __PhidgetTest__PhidgetMng__

#include <iostream>
#include <phidget21/phidget21.h>

#define DEVICES 4


/**\addtogroup PhidgetManager
         * Details
         *@{ */

/**< Phidget Manager Class */
class PhidgetMng {

public:

        /** \brief Constructor
         *
         *  Sets manager to Null
         */
    PhidgetMng();
        /** \brief Destructor
         *
         *
         */
    ~PhidgetMng();
    int connect();
        /** \brief Load phidgets and display properties
         *
         *  Fills param with the Ids of all the connected phidgets
         * \param ids _int16* Phidget Ids
         * \return _int16 1 on failure to connect to manager handle
         *
         */
    int display_devices(CPhidgetManagerHandle man);
        /** \brief Get number of connected phidgets
         *
         * \return _int16 number of connected phidgets
         *
         */
    int getPhidgetCount();
    const int * getPhidgetIds();



private:

    CPhidgetHandle* _phidgetList; /**< list of general phidget handles */
    int _phidgetCount; /**< number of connected phidgets */
    int _phidgetIds[DEVICES];

};

/** @} */
#endif /* defined(__PhidgetTest__PhidgetMng__) */
