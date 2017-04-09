/*
 * =========================================================================================
 * Name        : eventLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 2 - Data structures and Algorithms - Spring 2017
 *               This library contains functions used for event management
 * =========================================================================================
 */

#ifndef DSA162A2_EVENTLIB_H
#define DSA162A2_EVENTLIB_H

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>

#include "dsaLib.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define EVENT_CODE_SIZE     16
#define MAX_PARAM_SIZE      6
using namespace std;

typedef struct busEvent {
    char        code[EVENT_CODE_SIZE];
    double      params[MAX_PARAM_SIZE];

    busEvent() {
        strcpy(code, "0");// default event is "0"
    }
    busEvent(char* str) {
        strncpy(code, str, EVENT_CODE_SIZE - 1);
    }
    busEvent(string& str) {
        strncpy(code, str.data(), EVENT_CODE_SIZE - 1);
    }
    busEvent(busEvent& a) { // copy constructor
        memcpy(code, a.code, EVENT_CODE_SIZE);
        memcpy(params, a.params, MAX_PARAM_SIZE * sizeof(double));
    }
} busEvent_t;

void loadEvents(char* fName, L1List<busEvent_t> &eList);

#endif //DSA162A2_EVENTLIB_H
