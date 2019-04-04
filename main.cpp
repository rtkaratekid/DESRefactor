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

int main(int argc, char* argv[]) {

    double customerArrivalRate = atof(argv[1]);
    double maxServiceTime = atof(argv[2]);
    int randomNumSeed = atoi(argv[3]);
    string which = (argv[4]);

    //    double avgCustomerArrivalRate = 0.5;
    // double maxServiceTime = 15.2;
    // int randomNumSeed = 34543;

    double totalMinutes = 12.0 * 60.0;
    int numCustomers = int (totalMinutes * customerArrivalRate);
    double totalSeconds = totalMinutes * 60;
    double maxServiceTimeSeconds = maxServiceTime * 60;

    BankDES BankSim;
    EventStruct myEvent;
    srand(randomNumSeed);

    if(which == "-b"){

        // cout << "*****************************" << endl;
        // cout << "!!! Bank Queue Simulation !!!" << endl;
        // cout << "*****************************\n" << endl;

        

    //    cout << "Adding " << numCustomers << " customers.\n";
        for (int i = 0; i < numCustomers; i++) {
            myEvent.eventTime = fmod(rand(), totalSeconds);
            myEvent.duration = fmod(rand(), maxServiceTimeSeconds);
            myEvent.arrivalTime = myEvent.eventTime;
            myEvent.event = ARRIVAL;
            BankSim.addEvent(myEvent);
        }

        // cout << "Running...\n" << endl;
        BankSim.runSim();
        vector<double> bankTimes = BankSim.getServiceTimes();

        // cout << "Bank Service Times in Minutes: \n";
        // double averageTime = 0;
        // for(double d : bankTimes)
        //     averageTime += d;
        // averageTime /= bankTimes.size();
        // cout << "10th %ile " << bankTimes[(numCustomers * 0.1)] << endl;
        // cout << "50th %ile " << bankTimes[(numCustomers * 0.5)] << endl;
        // cout << "90th %ile " << bankTimes[(numCustomers * 0.9)] << endl;
        // cout << "Average Service Time : " << averageTime/60 << " minutes" << endl;


        cout << bankTimes[(numCustomers * 0.9)] << endl;


    } else if (which == "-m"){
        // cout << "************************************" << endl;
        // cout << "!!! Supermarket Queue Simulation !!!" << endl;
        // cout << "************************************\n" << endl;

        MarketDES MarketSim;

        for (int i = 0; i < numCustomers; i++) {
            myEvent.eventTime = fmod(rand(), totalSeconds);
            myEvent.duration = fmod(rand(), maxServiceTimeSeconds);
            myEvent.arrivalTime = myEvent.eventTime;
            myEvent.event = ARRIVAL;
            MarketSim.addEvent(myEvent);
        }

        // cout << "Running...\n" << endl;
        MarketSim.runSim();

        // cout << "\nSupermarket Service Times in Minutes: \n";
        // double averageTime = 0;
        // for(double d : MarketSim.serviceTimes)
        //     averageTime += d;
        // averageTime /= MarketSim.serviceTimes.size();
        // sort(MarketSim.serviceTimes.begin(), MarketSim.serviceTimes.end());
        // cout << "10th %ile " << MarketSim.serviceTimes[(numCustomers * 0.1)] / 60 << endl;
        // cout << "50th %ile " << MarketSim.serviceTimes[(numCustomers * 0.5)] / 60 << endl;
        // cout << "90th %ile " << MarketSim.serviceTimes[(numCustomers * 0.9)] / 60 << endl;
        // cout << "Average Service Time : " << averageTime/60 << " minutes" << endl;

        cout << MarketSim.serviceTimes[(numCustomers * 0.9)] << endl;

    } else {
        cout << "E R R O R  F O O L" << endl;
        return 666;
    }

    return 0;
}
