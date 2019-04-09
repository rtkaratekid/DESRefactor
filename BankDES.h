//
// Created by Tristan Mayfield on 2019-03-31.
//

#ifndef DISCRETESIMULATION_BANKDES_H
#define DISCRETESIMULATION_BANKDES_H

#include "Event.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <math.h>
#include <algorithm>

using namespace std;

class BankDES {

// our Discrete Event Simulation class
private:
    priority_queue<EventStruct, vector<EventStruct>, compareEventTime> eventQueue; // event queue
    queue<EventStruct> bankQueue; // wait queue
    double currentTime = 0;
    int tellersAvailable = 6; // we have 6 tellers arbitrarily
public:
    vector<double> serviceTimes;
    void addEvent(EventStruct &event);
    void addBankQueueCustomer(EventStruct &event);
    void onArrival(EventStruct nextEvent);
    void onDeparture(EventStruct nextEvent);
    void runSim();
};

#endif //DISCRETESIMULATION_BANKDES_H
