/* Day 4 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


/* Part 1 */

// Get start and stop int for both ranges
// no spaces in data
// elf1 = while not ','
// start_1 = while not '-'
// start_2 = while not ','

pair<pair<int, int>, pair<int, int>> getRanges(string entry) {
    pair<pair<int, int>, pair<int, int>> ranges;

    string number = ""; // to save end-points
    bool elf2 = false;  // Which elf we are looking at
    for(int i = 0; i < entry.length(); i++) {
        if(entry[i] == ',') {
            elf2 = true;    // Looking at second elf from now on
            ranges.first.second = stoi(number); // save number
            number = "";    // reset number
        }
        else if (entry[i] == '-') {
            // Check which elf's range it is
            if(elf2)
                ranges.second.first = stoi(number);
            else
                ranges.first.first = stoi(number);
            // reset number
            number = "";
        } else {
            // add letter to number
            number.push_back(entry[i]);
        }
        
    }
    // save end of second range
    ranges.second.second = stoi(number);
    return ranges;
}

bool isAnyContained(pair<pair<int, int>, pair<int, int>> ranges) {
    // Checks if either range is contained in the other by comparing 
    // start and stop values
    // Assuming no range is negative (e.g. 4-1)
    return ((ranges.first.first >= ranges.second.first && ranges.first.second <= ranges.second.second) ||
            (ranges.second.first >= ranges.first.first && ranges.second.second <= ranges.first.second));
}


int getNumberOfContained(string filename, bool (*criteria)(pair<pair<int, int>, pair<int, int>>)) {
    // criteria is the function checking the criteria
    ifstream FileReader(filename);
    string row;

    int total = 0;
    while(getline(FileReader, row)) {
        total += criteria(getRanges(row)); // returns true or false but seen as 1 or 0
    }
    return total;
}

/* Part 2 */
// Check if the ranges overlap at all
// Same thing, but check if at least one end-point is contained within other range

bool isAnyOverlap(pair<pair<int, int>, pair<int, int>> ranges) {
    return !(ranges.first.first > ranges.second.second ||
            ranges.first.second < ranges.second.first);
}




/* Main */

int main() {
    string filename = "data.txt";

    // Part 1
    cout << getNumberOfContained(filename, &isAnyContained) << endl;
 
    // Part 2
    cout << getNumberOfContained(filename, &isAnyOverlap) << endl;

    return 0;
}