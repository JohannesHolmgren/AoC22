/* Day 3 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;


int getPriority(char c) {
    // Get priority where 'a' to 'z' = 1 to 26
    // and 'A' to 'Z' = 27 to 52
    // since 'a' has ascii value 97, remove 96 if small
    // and likewise with 'A' has ascii value 65, remove
    // (65-27 = 38) otherwise
    if(int(c) < 96) return int(c) - 38;
    return int(c) - 96;
}

int findChar(string s, char searched) {
    // returns index of first occurence or -1
    for(int i = 0; i < s.length(); i++)
        if (s[i] == searched)
            return i; 
    return -1;
}

/* Part 1 */

// Add to collection first half
// Check in collection other half
// Assuming length of content is small, O(1) to check if contains
int getPrioritySum(string content) {
    int sum = 0;
    int length = content.length();
    string firstHalf;
    for(int i = 0; i < length; i++) {
        char c = content[i];
        if(i < length / 2) {    // length will always be divisible by 2 acc. to task
            // Add to array
            firstHalf.push_back(c);
        } else {
            // Check if exists in first half
            if(findChar(firstHalf, c) > -1) {
                sum += getPriority(c);
                // ignore for the rest of round by removing from firstHalf
                firstHalf.erase(remove(firstHalf.begin(), firstHalf.end(), c), firstHalf.end());
            }
        }
    }
    return sum;
}

/* Part 2 */

string getIntersect(string s1, string s2) {
    // returns a string which contains all matching letters
    // Doesn't matter if multiple instances of same letter occur since
    // only one letter will be left in the end
    string result = "";
    for(int i = 0; i < s1.length(); i++) {
        if(findChar(s2, s1[i]) > -1) {
            result.push_back(s1[i]);
        }
    }
    return result;
}

char getFirstMatch(string s1, string s2) {
    // Returns the first character that occurs in
    // both strings. Returns zero otherwise
    for(int i = 0; i < s1.length(); i++) {
        if(findChar(s2, s1[i]) > -1) {
            return s1[i];
        }
    }
    return 0;
}

int getTotalPrioritySum(string filename) {

    int sum = 0;
    ifstream FileReader(filename);
    string row;
    // Read row and row
    while(getline(FileReader, row)){
        sum += getPrioritySum(row);
    }
    return sum;
}

int getTotalBadgeSum(string filename) {
    int sum = 0;
    ifstream FileReader(filename);
    string row;

    int elfNum = 0; // first, 2nd or third elf
    string matched; // which letters that matches between elves
    // Read row and row
    while(getline(FileReader, row)){
        switch (elfNum)
        {
        case 0:     // first elf
            matched = row;
            elfNum++;
            break;
        case 1:     // second elf
        matched = getIntersect(matched, row);
            elfNum++;
            break;
        default:    // third elf
            char badge = getFirstMatch(matched, row);
            sum += getPriority(badge);
            elfNum = 0;
            break;
        }
        
    }
    return sum;
}



/* Main */
int main(){

    const string filename = "data.txt";

    // Part 1
    // int ans = getTotalPrioritySum(filename);
    // cout << ans << endl;

    // Part 2
    cout << getTotalBadgeSum(filename);

    return 0;
}