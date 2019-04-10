#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <math.h>
#include <algorithm>
#include "BankDES.h"
#include "MarketDES.h"

using namespace std;

//Didn't know quite where to put this...
void printStats(vector<double>& serviceTimes, string label) {
     cout << label << "\n";
     cout << serviceTimes.size() << "vector size\n";
     double averageTime = 0;
     for(double time : serviceTimes)
         averageTime += time;

     averageTime /= serviceTimes.size();
     sort(serviceTimes.begin(), serviceTimes.end());
     cout << "10th %ile " << serviceTimes[(serviceTimes.size() * 0.1)] << endl;
     cout << "50th %ile " << serviceTimes[(serviceTimes.size() * 0.5)] << endl;
     cout << "90th %ile " << serviceTimes[(serviceTimes.size() * 0.9)] << endl;
     cout << "Average Service Time : " << averageTime  << " minutes" << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cout << "Not enough arguments...\n";
        exit(1);
    }
    double customerArrivalRate = atof(argv[1]);
    double maxServiceTime = atof(argv[2]);
    int randomNumSeed = atoi(argv[3]);
    string which = (argv[4]);
    //    double avgCustomerArrivalRate = 0.5;
    // double maxServiceTime = 15.2;
    // int randomNumSeed = 34543;
    double totalMinutes = 12.0 * 60.0;
    int numCustomers = int (totalMinutes * customerArrivalRate);
    cout << numCustomers << "numCustomers \n";
    double totalSeconds = totalMinutes * 60;
    double maxServiceTimeSeconds = maxServiceTime * 60;
    srand(randomNumSeed);
    EventStruct myEvent;
    if(which == "-b"){
        BankDES BankSim;
        //    cout << "Adding " << numCustomers << " customers.\n";
        for (int i = 0; i < numCustomers; i++) {
            myEvent.eventTime = fmod(rand(), totalSeconds);
            myEvent.duration = fmod(rand(), maxServiceTimeSeconds);
            myEvent.arrivalTime = myEvent.eventTime;
            myEvent.event = ARRIVAL;
            BankSim.addEvent(myEvent);
        }
        BankSim.runSim();
        printStats(BankSim.serviceTimes, "Bank Wait Times:");
        cout << BankSim.serviceTimes[(numCustomers * 0.9)] << endl;
    } else if (which == "-m"){
        MarketDES MarketSim;
        for (int i = 0; i < numCustomers; i++) {
            myEvent.eventTime = fmod(rand(), totalSeconds);
            myEvent.duration = fmod(rand(), maxServiceTimeSeconds);
            myEvent.arrivalTime = myEvent.eventTime;
            myEvent.event = ARRIVAL;
            MarketSim.addEvent(myEvent);
        }
        MarketSim.runSim();
        printStats(MarketSim.serviceTimes, "Market Wait Times:");
        cout << MarketSim.serviceTimes[(numCustomers * 0.9)] << endl;
    } else {
        cout << "E R R O R  F O O L" << endl;
        return 666;
    }

    return 0;
}
