//
// Created by Tristan Mayfield on 2019-04-01.
//

#include "MarketDES.h"

// add a priority queue event
void MarketDES::addEvent(EventStruct &event) {
    eventQueue.push(event);
}

int MarketDES::getShortestLine(){
    // find the shortest wait time in the queues
    int minValueIndex = 0;
    for(int i = 0; i < checkers.size() - 1; ++i){
        if(checkers[i] > checkers[i + 1])
            minValueIndex = i + 1;
    }
    return minValueIndex;
}

void MarketDES::onArrival(EventStruct nextEvent) {
    int shortestLine = getShortestLine(); // find the shortest line
    nextEvent.line = shortestLine; // put customer in the shortest line

    // adding customer duration to line wait
    nextEvent.totalServiceTime = checkers.at(shortestLine) + nextEvent.duration;
    serviceTimes.push_back(nextEvent.totalServiceTime);

    // adding to the wait time for that checker's line
    checkers.at(shortestLine) += nextEvent.duration;

    // and seeing how long the customer has to wait to be served
    nextEvent.eventTime = currentTime + checkers.at(shortestLine);

    nextEvent.event = DEPARTURE;
    addEvent(nextEvent);
}

// run the simulation
void MarketDES::runSim() {
    while (!eventQueue.empty()) {
        EventStruct nextEvent = eventQueue.top(); // get next event in priority queue
        currentTime = nextEvent.eventTime; // incrementing the time count
        eventQueue.pop();
        switch (nextEvent.event) {
            case ARRIVAL:
                onArrival(nextEvent);
                break;
            case DEPARTURE:
                // decrementing the checker's line
                checkers.at(nextEvent.line) -= nextEvent.duration;
                break;
            default:
                cout << "ERROR: Should never get here! " << endl;
        }
    }
}
