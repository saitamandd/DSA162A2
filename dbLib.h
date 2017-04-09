/*
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 2 - Data structures and Algorithms - Spring 2017
 *               This library contains functions used for database management
 * =========================================================================================
 */

#ifndef DSA162A2_DBLIB_H
#define DSA162A2_DBLIB_H

#include <string.h>
#include <time.h>
#include <iostream>
#include <iomanip>

#include "dsaLib.h"
#include "eventLib.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define ID_MAX_LENGTH   16

typedef struct BusInfo {
    char    id[ID_MAX_LENGTH];
    time_t  timestamp;
    double  longitude, latitude;

    // default constructor
    BusInfo() {
        strcpy(id, "");
    }
    BusInfo(const char* busID) {
        strcpy(id, busID);
    }
    // copy constructor
    BusInfo(BusInfo& bus) : timestamp(bus.timestamp), longitude(bus.longitude), latitude(bus.latitude) {
        strcpy(id, bus.id);
    }
} BusInfo_t;

void    printBusInfo(BusInfo_t& b);
void    strPrintTime(char* des, time_t& t);
bool    parseBusInfo(char* pBuf, BusInfo_t& bInfo);
void    loadBusDB(char* fName, L1List<BusInfo_t> &db);
double  distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

bool processEvent(busEvent_t& event, L1List<BusInfo_t>& bList, void* pGData);// from processData.cpp

/// NOTE: student may create this function to allocate some global data
bool initBusGlobalData(void** pGData);
/// NOTE: student must defined this function if they use dynamically allocated global data.
/// If student do not use any dynamic global data, please define this function as empty function
/// in your code (file processData.cpp) as follows
/// void releaseBusGlobalData() {}
void releaseBusGlobalData(void* pGData);

void process(L1List<busEvent_t>& eventList, L1List<BusInfo_t>& bList);

#endif //DSA162A2_DBLIB_H
