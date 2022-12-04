#include <iostream>
#include <fstream>
#include <string.h>
#include <map>

using namespace std;


bool hasWon(char opMove, char myMove) {
    if(opMove == 'A' && myMove == 'Y')
        return true;
    if(opMove == 'B' && myMove == 'Z')
        return true;
    if(opMove == 'C' && myMove == 'X')
        return true;
    return false;
}

bool isTie(char opMove, char myMove) {
    if(opMove == 'A' && myMove == 'X')
        return true;
    if(opMove == 'B' && myMove == 'Y')
        return true;
    if(opMove == 'C' && myMove == 'Z')
        return true;
    return false;
}

int part1() {

    const int tie = 3;
    const int win = 6;

    int score = 0;
    // Play each round
    //  Read line
    //    Split on space
    //  Compare and see if win
    //    If win: add score
    //    Else if tie: add score
    //    Add points for input
    // Sum all scores

    // Match letter to score
    map<char, int> choicePts = {
            {'X', 1},
            {'Y', 2},
            {'Z', 3}
        };

    // filename
    string filename = "data.txt";
    // create file reader stream
    ifstream FileReader(filename);

    // Read row and row
    while(getline(FileReader, filename)){
        int roundPts = 0;
        char opMove = filename[0];
        char myMove = filename[2];
        // Check if tie
        if(isTie(opMove, myMove)) {
            roundPts += tie;
        }
        // Check if win
        else if (hasWon(opMove, myMove)) {
            roundPts += win;
        }
        // Add choice pts
        roundPts += choicePts[myMove];
        score += roundPts;
        roundPts = 0;
    }

    return score;

}

// Part 2

const char CHOICE[3] = {'A', 'B', 'C'};
map<char, int> INDEX = {
    {'A', 0},
    {'B', 1},
    {'C', 2}
};

template<typename Type>
Type getAdjacent(Type arr[], int size, int pos, int dir) {
    /*  arr: array to get adjacent from
        size: size of arr
        pos: pos to take adjacent from
        dir: direction to take adjacent from   
     */
    return arr[(pos + dir + size) % size]; // add size since -1 do not result in 2
}

char getMove(char opMove, char strat) {
    const char LOSE = 'X'; 
    const char TIE = 'Y';
    const char WIN = 'Z';

    // should tie. return opMove
    if(strat == TIE)
        return opMove;
    // Should win. Return next move mod length
    int size = sizeof(CHOICE)/sizeof(CHOICE[0]);
    if(strat == WIN) {
        return getAdjacent(CHOICE, size, INDEX[opMove], 1);
        // return CHOICE[(INDEX[opMove] + 1) % (sizeof(INDEX)/sizeof(INDEX[0]))];
    }
    // Lose
    else {
        return getAdjacent(CHOICE, size, INDEX[opMove], -1);
    }    
}

int getScore(char myMove, char strat) {
    /* Returns score for one round */

    map<char, int> choicePts = {
        {'A', 1},
        {'B', 2},
        {'C', 3}
    };

    map<char, int> stratPts = {
        {'X', 0},
        {'Y', 3},
        {'Z', 6}
    };

    return choicePts[myMove] + stratPts[strat];
}


int getTotalScore(string filename){
    // create file reader stream
    ifstream FileReader(filename);

    int score = 0;
    // Read row and row
    while(getline(FileReader, filename)){
        int roundPts = 0;
        char opMove = filename[0];
        char strat = filename[2];
        // get my move
        char myMove = getMove(opMove, strat);
        score += getScore(myMove, strat);
    }
    return score;
}


int main() {

    // Part 1
    // cout << part1() << endl;
    
    // Part 2
    string filename = "data.txt";
    int score = getTotalScore(filename);
    cout << score << endl;
    return 0;
}