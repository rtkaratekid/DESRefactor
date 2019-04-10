//
// Created by Tristan Mayfield on 2019-03-31.
//

#ifndef DISCRETESIMULATION_EVENT_H
#define DISCRETESIMULATION_EVENT_H



#import <iostream>

using namespace std;

typedef enum {
    ARRIVAL, DEPARTURE
} EventType;

// define an event struct to store events
typedef struct {
    double eventTime; // time event is to be completed
    double duration; // total customer service time
    double arrivalTime;
    int line; // for supermarket use only
    EventType event;
} EventStruct;

struct compareEventTime {
    bool operator()(const EventStruct &lhs, const EventStruct &rhs) const {
        return lhs.eventTime > rhs.eventTime;
    }
};

#endif //DISCRETESIMULATION_EVENT_H