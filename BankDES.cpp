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
    event.waitTime = currentTime;
}

// run the simulation
void BankDES::runSim() {
    while (!eventQueue.empty()) {
        EventStruct nextEvent = eventQueue.top(); // get next event in priority queue
        currentTime = nextEvent.eventTime; // updating the time
        eventQueue.pop();
        switch (nextEvent.event) {
            case ARRIVAL:
                if (tellersAvailable) {
                    // enter departure event in eventQueue
                    nextEvent.eventTime = currentTime + nextEvent.duration;
                    nextEvent.totalServiceTime = (nextEvent.eventTime - nextEvent.arrivalTime) / 60; // divide by 60 to get minutes

                    nextEvent.event = DEPARTURE;
                    addEvent(nextEvent);
                    tellersAvailable--;
                } else {
                    // no tellers available, put customer in bank queue
                    addBankQueueCustomer(nextEvent);
                }
                break;
            case DEPARTURE:
                if (!bankQueue.empty()) {
                    // pushing back into my served customers
                    servedCustomers.push_back(nextEvent);

                    EventStruct nextCustomer = bankQueue.front(); // getting the next customer from the bank queue
                    bankQueue.pop();
                    nextCustomer.eventTime = currentTime + nextEvent.duration;

                    // calculate total service time, including waits
                    nextCustomer.totalServiceTime = ((currentTime + nextCustomer.duration) - nextCustomer.arrivalTime) / 60;
                    nextCustomer.event = DEPARTURE;
                    addEvent(nextCustomer);
                } else {
                    // pushing back into my served customers
                    servedCustomers.push_back(nextEvent);
                    tellersAvailable++;
                }
                break;
            default:
                cout << "ERROR: Should never get here! " << endl;
        }
    }
}

// probably could've done this a bit better
vector<double> BankDES::getServiceTimes() {
    vector<double> ret;
    for(EventStruct e : servedCustomers) {
        ret.push_back(e.totalServiceTime);
    }
    sort(ret.begin(), ret.end());
    return ret;
}
