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
    pair<int, int> head = make_pair(0, 4); // position of head (start at s= (0, 0))
    pair<int, int> tail = make_pair(0, 4); // position of tail (start at s= (0, 0))
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

int main()
{
    const string FILENAME = "data.txt";
    vector<string> lines = readData(FILENAME);
    vector<pair<char, int>> data = splitLines(lines);
    int nVisited = getTotalVisitedPositions(data);
    cout << "Part 1: " << nVisited << endl;
    return 0;
}