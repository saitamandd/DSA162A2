/*
 * ==========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 2 - Data structures and Algorithms - Spring 2017
 * ==========================================================================================
 */
#include <iostream>

#include "eventLib.h"
#include "dbLib.h"

using namespace std;

#define GPS_DISTANCE_ERROR 0.005

bool initBusGlobalData(void** pGData) {
    // TODO: allocate and initialize global data
    // return false if failed
    return true;
}

void releaseBusGlobalData(void* pGData) {
    // TODO: do your cleanup, left this empty if you don't have any dynamically allocated data
}

bool processEvent(busEvent_t& event, L1List<BusInfo_t>& bList, void* pGData) {
    // TODO: Your code goes here
    // return false for invlaid events
    return true;
}


