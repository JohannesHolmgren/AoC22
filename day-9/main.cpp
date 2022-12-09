#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stdlib.h>

using namespace std;

/* Data reading */
vector<string> readData(string filename)
{
    vector<string> data;
    ifstream fin(filename);
    string row;
    while (getline(fin, row))
    {
        data.push_back(row);
    }
    return data;
}

/* Part 1 */
vector<pair<char, int>> splitLines(vector<string> lines)
{
    vector<pair<char, int>> data;
    for (int i = 0; i < lines.size(); i++)
    {
        pair<char, int> p;
        p.first = lines[i][0];
        string number = lines[i].substr(2, lines[i].length());
        p.second = stoi(number);
        data.push_back(p);
    }
    return data;
}

int getTotalVisitedPositions(vector<pair<char, int>> data)
{

    map<char, pair<int, int>> directions =
        {
            {'L', make_pair(-1, 0)},
            {'U', make_pair(0, -1)},
            {'R', make_pair(1, 0)},
            {'D', make_pair(0, 1)}}; // what x- and y-direction the letter tracks
    set<pair<int, int>> visited;
    pair<int, int> head = make_pair(0, 4); // position of head (start at s= (0, 4))
    pair<int, int> tail = make_pair(0, 4); // position of tail (start at s= (0, 4))
    // add start node to visited
    visited.insert(tail);
    for (int i = 0; i < data.size(); i++)
    {
        char dir = data[i].first;
        int steps = data[i].second;
        pair<int, int> direction = directions[dir];
        // step one step at a time
        for (int s = 0; s < steps; s++)
        {
            // move the head
            head.first += direction.first;
            head.second += direction.second;
            // check if tail is not connected
            int diffX = abs(head.first - tail.first);
            int diffY = abs(head.second - tail.second);
            // still connected. Continue;
            if (diffX <= 1 && diffY <= 1)
            {
                continue;
            }

            // lost connection. Check two cases:
            //  1. only differs in one direction. Move that direction
            if (diffX > 1 && diffY == 0)
            {
                // move same direction as head
                tail.first += direction.first;
            }
            else if (diffY > 1 && diffX == 0)
            {
                // move same direction as head
                tail.second += direction.second;
            }
            //  2. differs in two directions. Move diagonally towards head
            else
            {
                int dirX = (head.first - tail.first) / abs(head.first - tail.first);
                int dirY = (head.second - tail.second) / abs(head.second - tail.second);
                tail.first += dirX;
                tail.second += dirY;
            }
            // add tail's position to visited;
            // cout << "at " << "(" << head.first << ", " << head.second << ") ";
            // cout << "(" << tail.first << ", " << tail.second << ")" << endl;

            visited.insert(tail);
        }
    }
    // return number of visited
    return visited.size();
}

/* Part 2 - same as above but modified */
int getTotalVisitedPositions2(vector<pair<char, int>> data)
{

    map<char, pair<int, int>> directions =
        {
            {'L', make_pair(-1, 0)},
            {'U', make_pair(0, -1)},
            {'R', make_pair(1, 0)},
            {'D', make_pair(0, 1)}}; // what x- and y-direction the letter tracks
    set<pair<int, int>> visited;
    const int TAIL_SIZE = 9;
    const int last = TAIL_SIZE - 1;
    // position of head (start at s= (0, 0))
    pair<int, int> head = make_pair(11, 15);
    // initialise tail with start at (0, 0)
    vector<pair<int, int>> tail(TAIL_SIZE);
    for (int i = 0; i < TAIL_SIZE; i++)
    {
        tail[i] = make_pair(11, 15);
    }

    // add start node to visited
    visited.insert(tail[last]);
    for (int i = 0; i < data.size(); i++)
    {
        // cout << "Headeee: " << head.first << "," << head.second << endl;
        char dir = data[i].first;
        int steps = data[i].second;
        pair<int, int> direction = directions[dir];
        // step one step at a time
        for (int s = 0; s < steps; s++)
        {
            // move the head
            head.first += direction.first;
            head.second += direction.second;
            // cout << "H: " << head.first << ", " << head.second << endl;
            // Move each tail-part
            for (int t = 0; t < TAIL_SIZE; t++)
            {

                // get pointers to current and previous part
                pair<int, int> *current = &tail[t];
                pair<int, int> *previous;
                if (t == 0)
                    previous = &head;
                else
                    previous = &tail[t - 1];
                // check if tail is not connected
                int diffX = abs(previous->first - current->first);
                int diffY = abs(previous->second - current->second);
                // still connected. Continue;
                if (diffX <= 1 && diffY <= 1)
                {
                    // cout << current->first << ", " << current->second << endl;
                    continue;
                }
                // lost connection. Check two cases:
                //  1. only differs in one direction. Move that direction
                if (diffX > 1 && diffY == 0)
                {
                    // move same direction as head
                    current->first += direction.first;
                }
                else if (diffY > 1 && diffX == 0)
                {
                    // move same direction as head
                    current->second += direction.second;
                }
                //  2. differs in two directions. Move diagonally towards head
                else
                {
                    int dirX = (previous->first - current->first) / abs(previous->first - current->first);
                    int dirY = (previous->second - current->second) / abs(previous->second - current->second);
                    current->first += dirX;
                    current->second += dirY;
                }
                // cout << current->first << ", " << current->second << endl;
            }
            if (s == 2)
            {
            }

            cout << "Head: " << head.first << "," << head.second << endl;
            for (int i = 0; i < TAIL_SIZE; i++)
            {
                cout << i << ": (" << tail[i].first << "," << tail[i].second << ")" << endl;
            }
            // add tail's last part's position to visited;
            // cout << "added " << tail[last].first << ", " << tail[last].first << endl;
            visited.insert(tail[last]);
        }
    }
    // return number of visited
    return visited.size();
}

int main()
{
    const string FILENAME = "data.txt";
    vector<string> lines = readData(FILENAME);
    vector<pair<char, int>> data = splitLines(lines);
    // Part 1
    int nVisited = getTotalVisitedPositions(data);
    cout << "Part 1: " << nVisited << endl;
    // Part 2
    int nVisited2 = getTotalVisitedPositions2(data);
    cout << "Part 2: " << nVisited2 << endl;
    return 0;
}