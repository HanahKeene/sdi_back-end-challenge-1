#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Struct to represent each car size
struct CarSize {
    string name;
    int capacity;
    int cost;
};

// Function to find the cheapest combination of cars
void findCheapestCost(int seatsNeeded, const vector<CarSize>& carSizes) {
    // Vector to store the minimum cost for each number of seats up to seatsNeeded
    vector<int> minCost(seatsNeeded + 1, numeric_limits<int>::max());
    // Vector to store the last used car size index for each number of seats up to seatsNeeded
    vector<int> lastCarIndex(seatsNeeded + 1, -1);

    minCost[0] = 0; // Base case: 0 seats require 0 cost

    // Process for each number of seats from 1 to seatsNeeded
    for (int seats = 1; seats <= seatsNeeded; ++seats) {
        // Check each car size to find the minimum cost
        for (int j = 0; j < carSizes.size(); ++j) {
            int currentCost = carSizes[j].cost;
            int remainingSeats = seats - carSizes[j].capacity;

            if (remainingSeats >= 0 && minCost[remainingSeats] != numeric_limits<int>::max()) {
                if (minCost[seats] > minCost[remainingSeats] + currentCost) {
                    minCost[seats] = minCost[remainingSeats] + currentCost;
                    lastCarIndex[seats] = j;
                }
            }
        }
    }

    // Construct the solution output
    int remainingSeats = seatsNeeded;
    vector<string> solution;

    while (remainingSeats > 0) {
        int carIndex = lastCarIndex[remainingSeats];
        solution.push_back(carSizes[carIndex].name);
        remainingSeats -= carSizes[carIndex].capacity;
    }

    // Output the result
    cout << "Optimized solution:" << endl;
    for (int i = 0; i < solution.size(); ++i) {
        cout << solution[i];
        if (i < solution.size() - 1) {
            cout << " x ";
        }
    }
    cout << endl;
    cout << "Total = PHP " << minCost[seatsNeeded] << endl;
}

int main() {
    // Define car sizes and their capacities and costs
    vector<CarSize> carSizes = {
        {"S", 5, 5000},
        {"M", 9, 8000},  // Changed Medium size capacity to 9
        {"L", 15, 12000}
    };

    // Read number of seats from user input
    int seatsNeeded;
    cout << "Please input number (seat): ";
    cin >> seatsNeeded;

    // Find the cheapest cost for the given number of seats
    findCheapestCost(seatsNeeded, carSizes);

    return 0;
}
