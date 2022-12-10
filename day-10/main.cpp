/* Day 10 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stdlib.h>

using namespace std;

vector<string> splitString(string entry, char = ' ');

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

/* String split */
vector<string> splitString(string entry, char delim)
{
    /* Divides string into words separated by delim */
    vector<string> parts;
    string part = "";
    for (int i = 0; i < entry.length(); i++)
    {
        if (entry[i] == delim)
        {
            parts.push_back(part);
            part = "";
        }
        else
            part.push_back(entry[i]);
    }
    if (part.length() > 0)
        parts.push_back(part);
    return parts;
}

/* Data splitting */
vector<pair<string, int>> getInstructions(vector<string> lines)
{
    vector<pair<string, int>> instructions;
    for (int i = 0; i < lines.size(); i++)
    {
        pair<string, int> p;
        vector<string> parts = splitString(lines[i]);
        p.first = parts[0]; // save instruction
        // addx also uses data. save that too
        if (parts[0] == "addx")
            p.second = stoi(parts[1]);
        instructions.push_back(p);
    }
    return instructions;
}

/* Part 1 */
int runProgram(vector<pair<string, int>> instructions)
{
    // Runs the instructions and calculates the signal strength
    // for the 20th, 60th, 100th, 140th, 180th and 220th clock cycle
    // by multiplying the value of register X with the current clock cycle
    // To check if 20 or 20 + 40*N:
    //  Take (cycle - 20) mod 40. will be 0 only in the cases above

    // Check if time to read signal strength
    auto isReadTime = [](int cycle)
    { return !(cycle - 20 % 40); };
}

/* Main */
int main()
{
    const string FILENAME = "data.txt";
    vector<string> data = readData(FILENAME);
    vector<pair<string, int>> instructions = getInstructions(data);

    return 0;
}