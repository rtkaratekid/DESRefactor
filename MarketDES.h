//
// Created by Tristan Mayfield on 2019-04-01.
//

#ifndef DISCRETESIMULATION_MARKETDES_H
#define DISCRETESIMULATION_MARKETDES_H

#include <vector>
#include <queue>
#include "Event.h"

using namespace std;

class MarketDES {
private:
    priority_queue<EventStruct, vector<EventStruct>, compareEventTime> eventQueue; // event queue

    // vector of doubles to track the wait times for each of the market checkers
    // 6 to reflect the number of checkers
    vector<double> checkers = {0, 0, 0, 0, 0, 0};
    double currentTime = 0;
    int getShortestLine();

public:
    vector<double> serviceTimes; // where I put my times
    void addEvent(EventStruct &event);
    void onArrival(EventStruct event);
    void runSim();
};


#endif //DISCRETESIMULATION_MARKETDES_H
