#include <iostream>

#include "dsaLib.h"
#include "eventLib.h"
#include "dbLib.h"

using namespace std;



/// This function displays the content of database
void display(L1List<BusInfo_t>& bList) {
    cout.flush();
    bList.traverse(printBusInfo);
}

int main(int narg, char** argv) {
    L1List<busEvent_t>  eventList;
    L1List<BusInfo_t>   db;// database of BusInfo
    loadEvents(argv[1], eventList);
    loadBusDB(argv[2], db);

    cout << fixed << setprecision(12);// preset for floating point numbers
    /// Process events
    process(eventList, db);

    cout << resetiosflags(ios::showbase) << setprecision(-1);

    return 0;
}