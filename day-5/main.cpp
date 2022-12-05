/* Day-5 */

#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>
#include <vector>
#include <stack>    // should not use
#include <deque>
#include <map>

using namespace std;


bool isDigit(char c) {
    const string DIGITS = "0123456789";
    for(int i = 0; i < DIGITS.length(); i++)
        if (c == DIGITS[i])
            return true;
    return false;
}

/* Part 1 */
// Need to get starting position and instructions
// Starting position is everything before blank row

vector<deque<char>> getStartPosition(vector<string> input) {
    vector<deque<char>> stacks; // this will be return value
    map<int, int> index; // Which index each stack is stored at
    const string lastRow = input.back();
    input.pop_back();   // remove last row (the index row)
    for(int i = 0; i < lastRow.length(); i++) {
        if(isDigit(lastRow[i])) {
            index[(int)(lastRow[i]-'0') - 1] = i;   // convert digit to int and take minus 1
            stacks.push_back(deque<char>());

        }
    }
    // From above its known which index each stack is at. Add to stacks
    for(int row = 0; row < input.size(); row++) {
        string level = input[row];
        // iterate through map
        map<int, int>::iterator it;
        for(it = index.begin(); it != index.end(); it++) {
            // Add letter at index to stack if is a char and not empty position
            if(isalpha(level[it->second])) {
                stacks[it->first].push_front(level[it->second]);
            }
        }
    }

    return stacks;
}

void getData(string input, int data[]) {
    // Get number, from and to from input
    // data will contain the data returned
    // stores [amount, from, to]

    int index = 0;
    string digit = "";
    int i = 0;
    while(index < 3) {
        while(!isDigit(input[i]))
        i++;
    // found a digit. Add to digit string
    while(isDigit(input[i])){
        digit.push_back(input[i]);
        i++;
    }
    // digit done. Add to data at index
    data[index] = stoi(digit);
    digit = "";
    index++;
    // repeat for each number
    }
}

void moveAround(string instruction, vector<deque<char>>& position) {
    int data[3];
    getData(instruction, data);
    for(int i = 0; i < data[0]; i++) {
        // data[0] says how many times we should move from data[1] to data[2]
        if(position[data[1]-1].size() <= 0) // If any one stack is empty
            return;
        position[data[2]-1].push_back(position[data[1]-1].back()); // add element
        position[data[1]-1].pop_back();   // remove element
    }
}


string getTopRow(vector<string> rows, void(*moveFunc)(string, vector<deque<char>>&)) {
    // return value
    string topRow;

    vector<string> input;
    bool readingInput = true;
    vector<deque<char>> position;

    for(int i = 0; i < rows.size(); i++){
        string row = rows[i];
        if (readingInput) {
            if(row.length() == 0) {
                // end of input
                readingInput = false;
                // get startPos
                position = getStartPosition(input);
            } else {
                // add to input
                input.push_back(row);
            }
        }
        else {
            moveFunc(row, position);
        }
    }

    // Get top elements
    for(int i = 0; i < position.size(); i++) {
        cout << position[i].back();
        topRow[i] = position[i].back();
    }
    return topRow;
}

// Read starting position into stacks
// Push around NOTE!! starts index at 1

/* Part 2 */


void moveManyAround(string instruction, vector<deque<char>>& position) {
    // Move to temporary stack and then move to new stack gets correct order
    int data[3];
    deque<char> tmp;
    tmp.clear();
    getData(instruction, data);
    for(int i = 0; i < data[0]; i++) {
        // data[0] says how many times we should move from data[1] to data[2]
        if(position[data[1]-1].size() <= 0) // If any one stack is empty
            return;
        // position[data[2]-1].push_back(position[data[1]-1].back()); // add element
        tmp.push_back(position[data[1]-1].back());
        position[data[1]-1].pop_back();   // remove element
    }
    // move all from tmp stack to new stack
    for(int i = 0; i < data[0]; i++) {
        position[data[2]-1].push_back(tmp.back());
        tmp.pop_back();
    }
}

/* Main */
int main() {

    const string FILENAME = "data.txt";

    // cout << getTopRow(FILENAME) << endl;

    ifstream FileReader(FILENAME);
    string row;

    vector<string> rows;

    while(getline(FileReader, row)){
        rows.push_back(row);
    }

    // string result = getTopRow(rows, &moveAround);
    // cout << result << endl;


    // Part 2
    string result2 = getTopRow(rows, &moveManyAround);
    cout << result2 << endl;

}