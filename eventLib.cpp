/*
 * =========================================================================================
 * Name        : eventLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 2 - Data structures and Algorithms - Spring 2017
 *               This library contains functions used for event management
 * =========================================================================================
 */

#include "eventLib.h"


/// NOTE: each event will be separated by endline character
void loadEvents(char* fName, L1List<busEvent_t> &eList) {
    ifstream inFile(fName);

    if (inFile) {
        string line;
        while (getline(inFile , line)) {
            /// On Windows, lines on file ends with \r\n. So you have to remove \r
            if (line[line.length() - 1] == '\r')
                line.erase(line.length() - 1);
            if (line.length() < 1) continue;

            istringstream iss(line);
            if (iss) {
                string sub;
                iss >> sub;
                if (sub.length()) {
                    busEvent_t __e(sub);
                    int i = 0;
                    while (iss) {
                        if (i >= MAX_PARAM_SIZE) break;
                        iss >> __e.params[i++];
                    }
                    eList.insertHead(__e);
                }
            }
        }
        eList.reverse();
        inFile.close();
    }
    else {
        cout << "The file is not found!";
    }
}
