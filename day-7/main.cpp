#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

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

const int MAX_SIZE = 100000;
const int REQUIRED_SPACE = 30000000;
const int DISC_SPACE = 70000000;

vector<string> getParts(string entry) {
    /* Divides string into words separated by space */
    vector<string> parts;
    string part = "";
    for(int i = 0; i < entry.length(); i++) {
        if(entry[i] == ' ') {
            parts.push_back(part);
            part = "";
        } else {
            part.push_back(entry[i]);
        }
    }
    if(part.length() > 0)
        parts.push_back(part);
    return parts;
}

int getSize(vector<string> data, vector<int>& dirSizes, int& index, int *totalSum) {
    int size = 0;
    while (index < data.size())
    {
        vector<string> parts = getParts(data[index]);
        // Instruction
        if(parts[0] == "$") {
            // Listing files and directories
            if (parts[1] == "ls") {
                // Iterate through all coming until finding new instruction
                index++;
                continue;
            // Jumping around
            } else if (parts[1] == "cd") {
                if (parts[2] == "..") {
                    // Done with this directory
                    if(size <= MAX_SIZE){
                        *totalSum += size;
                    }
                    index++;
                    // cout << ".." << " " << index << endl;
                    dirSizes.push_back(size);
                    return size;
                }
                // Jump to sub-directory. Repeat this function with new dir name
                // cout << parts[2] << endl;
                int subSize = getSize(data, dirSizes, ++index, totalSum);
                size += subSize;
                // cout << parts[2] << " = " << subSize << endl;
            }
        // Data
        } else {
            // Directory
            if (parts[0] == "dir") {
                // we do not care about dir names
                index++;
                continue;
            // File
            } else {
                // Is file. Add to size
                size += stoi(parts[0]);
                index++;
            }
        }
    }
    // Done with data
    if(size <= MAX_SIZE){
        *totalSum += size;
    }
    // Add to all dirs
    dirSizes.push_back(size);
    // cout << size << " at index " << index << endl;
    return size;
}

int getTotalSize(vector<string> data, vector<int>& dirSizes, int& rootSize)
{
    int totalSmallSize;
    int startIndex = 1;
    rootSize = getSize(data, dirSizes, startIndex, &totalSmallSize);   //start at index 1 since cd / is unnecessary
    return totalSmallSize;
}

/* Part 2 */
// (Change current code)
// Save all dir sizes
// When returning size of dir, check if size is greater than required. Save size
// When finished, pick the smallest

int findSmallest(const vector<int> values, int rootSize, int discSize) {
    int available = discSize - rootSize;
    int needed = REQUIRED_SPACE - available;
    if (values.size() < 1) {
        throw length_error("LenghtError: 'values' must be of at least size 1");
    }
    if (values.size() == 1) {
        return values[0];
    }
    int smallest = -1;
    for(int i = 1; i < values.size(); i++) {
        // Large enough
        if(values[i] >= needed) {
            // cout << values[i] << endl;
            // First element that is large enough
            if (smallest == -1) {
                smallest = values[i];
            }
            // Not first element that is large enough. Check if smallest
            else {
                if (values[i] < smallest) {
                    smallest = values[i];
                }
            }
        }
    }
    return smallest;
}

/* Main */
int main()
{
    const string FILENAME = "data.txt";
    vector<string> data = readData(FILENAME);
    vector<int> dirSizes;
    int rootSize;

    int totalSize = getTotalSize(data, dirSizes, rootSize);

    cout << "Part 1: " << totalSize << endl;
    cout << "Part 2: " << findSmallest(dirSizes, rootSize, DISC_SPACE) << endl;
}