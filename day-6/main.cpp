/* Day-5 */

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <map>

using namespace std;

/* Part 1 */
const int SEQ_LENGTH = 14;

template<typename T>
bool contains(deque<T> const seq, T searched) {
    /*  Check if 'searched' lies is contained in 'seq'
        seq must be iterable
     */
    for(int i = 0; i < seq.size(); i++) {
        if(searched == seq[i])
            return true;
    }
    return false;
}

template<typename T>
bool isUnique(deque<T> const seq) {
    map<char, int> content;
    for(int i = 0; i < seq.size(); i++) {
        if(content[seq[i]] > 0)
            return false;
        content[seq[i]] = 1;
    }
    return true;
}

int getStartIndex(string buffer) {
    deque<char> seq;
    int i;
    for(i=0; i<SEQ_LENGTH; i++)
        seq.push_back(buffer[i]);
    if(isUnique(seq))
        return i + 1;
    for(i=SEQ_LENGTH; i < buffer.length(); i++) {
        seq.pop_front();
        seq.push_back(buffer[i]);
        if(isUnique(seq))
            return i + 1;
    }
    // No unique found in buffer
    return -1;
}

/* Part 2 */

/* Main */

int main() {
    const string FILENAME = "data.txt";

    ifstream fin(FILENAME);
    string data;
    getline(fin, data);
    cout << getStartIndex(data) << endl;
    

}