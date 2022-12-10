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
int runProgram(const vector<pair<string, int>> instructions)
{
    // Runs the instructions and calculates the signal strength
    // for the 20th, 60th, 100th, 140th, 180th and 220th clock cycle
    // by multiplying the value of register X with the current clock cycle
    // To check if 20 or 20 + 40*N:
    //  Take (cycle - 20) mod 40. will be 0 only in the cases above

    // When program should terminate
    const int MAX_CYCLES = 220;
    // Map for number of cycles for each instruction
    map<string, int>
        instructionCycles = {
            {"noop", 1},
            {"addx", 2}};

    // Check if time to read signal strength
    auto isReadTime = [](int cycle)
    { return !((cycle - 20) % 40); };

    int sumSignalStrengths = 0;

    int cycle = 0;
    int regX = 1;

    for (int i = 0; i < instructions.size(); i++)
    {
        pair<string, int> instr = instructions[i];
        if (instr.first == "noop")
        {
            for (int step = 0; step < instructionCycles["noop"]; step++)
            {
                cycle++;
                if (isReadTime(cycle))
                {
                    sumSignalStrengths += cycle * regX;
                    cout << "sumSignalStrength: " << sumSignalStrengths << " at cycle " << cycle << " with a = " << regX << endl;
                }
                // If program is much larger than 220, another signal strength could be counted
                else if (cycle > MAX_CYCLES)
                {
                    return sumSignalStrengths;
                }
            }
        }
        else if (instr.first == "addx")
        {
            // go through the steps for addx
            for (int i = 0; i < instructionCycles[instr.first]; i++)
            {
                cycle++;
                if (isReadTime(cycle))
                {
                    sumSignalStrengths += cycle * regX;
                    cout << "sumSignalStrength: " << sumSignalStrengths << " at cycle " << cycle << " with X = " << regX << endl;
                }
                // If program is much larger than 220, another signal strength could be counted
                else if (cycle > MAX_CYCLES)
                {
                    return sumSignalStrengths;
                }
            }
            regX += instr.second;
        }
    }
    return sumSignalStrengths;
}

/* Main */
int main()
{
    const string FILENAME = "data.txt";
    vector<string> data = readData(FILENAME);
    vector<pair<string, int>> instructions = getInstructions(data);
    int signalStrength = runProgram(instructions);
    cout << "Part 1: " << signalStrength << endl;
    return 0;
}