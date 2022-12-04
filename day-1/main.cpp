#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
using namespace std;

void readData(string filename) {
    ifstream fout(filename);

    int length = 0;
    while(getline(fout, filename)){
        length++;
    }
}

void part1() {

    // read data
    // save max
    // loop through data
    // sum together all until blank row
    // max = max(max, sum)
    // return max

    string filename = "data.txt";
    ifstream fout(filename);

    int max = 0;
    int sum = 0;
    while(getline(fout, filename)){
        int entry;
        if(filename.length() > 0) {
            // Is an int. Add to sum
            entry = stoi(filename);
            sum += entry;
        } 
        else {
            // blank row. Check with max and new sum
            if(sum > max)
                max = sum;
            sum = 0;
        }
    }
    cout << max << endl;
}


// Part 2: Same but sum of top three elves
void part2() {

    string filename = "data.txt";
    ifstream fout(filename);

    int max = 0;
    int max2 = 0;
    int max3 = 0;
    int sum = 0;
    while(getline(fout, filename)){
        int entry;
        if(filename.length() > 0) {
            // Is an int. Add to sum
            entry = stoi(filename);
            sum += entry;
        } 
        else {
            // blank row. Check with maxes and new sum
            if(sum > max) {
                max3 = max2;
                max2 = max;
                max = sum;
            }
            else if (sum > max2) {
                max3 = max2;
                max2 = sum;
            }
            else if (sum > max3) {
                max3 = sum;
            }
            // reset sum
            sum = 0;
        }
    }
    cout << (max + max2 + max3) << endl;
}


int main() {

    part1();
    part2();

    return 0;
}