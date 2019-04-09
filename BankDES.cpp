//
// Created by Tristan Mayfield on 2019-03-31.
//

#include "BankDES.h"

// add a priority queue event
void BankDES::addEvent(EventStruct &event) {
    eventQueue.push(event);
}

// add a bank queue customer (not really an event)
void BankDES::addBankQueueCustomer(EventStruct &event) {
    bankQueue.push(event);
}

void BankDES::onArrival(EventStruct nextEvent) {
    if (tellersAvailable) {
        // enter departure event in eventQueue
        nextEvent.eventTime = currentTime + nextEvent.duration;
//        nextEvent.totalServiceTime = (nextEvent.eventTime - nextEvent.arrivalTime) / 60; // divide by 60 to get minutes
        serviceTimes.push_back((nextEvent.eventTime - nextEvent.arrivalTime) / 60);
        nextEvent.event = DEPARTURE;
        addEvent(nextEvent);
        tellersAvailable--;
    } else {
        // no tellers available, put customer in bank queue
        addBankQueueCustomer(nextEvent);
    }
}

void BankDES::onDeparture(EventStruct nextEvent) {
    if (!bankQueue.empty()) {
        EventStruct nextCustomer = bankQueue.front(); // getting the next customer from the bank queue
        bankQueue.pop();
        nextCustomer.eventTime = currentTime + nextEvent.duration;

        // calculate total service time, including waits
        serviceTimes.push_back((nextEvent.eventTime - nextEvent.arrivalTime) / 60);
        nextCustomer.event = DEPARTURE;
        addEvent(nextCustomer);
    } else {
        tellersAvailable++;
    }
}

// run the simulation
void BankDES::runSim() {
    while (!eventQueue.empty()) {
        EventStruct nextEvent = eventQueue.top(); // get next event in priority queue
        currentTime = nextEvent.eventTime; // updating the time
        eventQueue.pop();
        switch (nextEvent.event) {
            case ARRIVAL:
                onArrival(nextEvent);
                break;
            case DEPARTURE:
                onDeparture(nextEvent);
                break;
            default:
                cout << "ERROR: Should never get here! " << endl;
        }
    }
    sort(serviceTimes.begin(), serviceTimes.end());
}
