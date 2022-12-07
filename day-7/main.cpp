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

int getSize(map<string, int> sizes, vector<string> data, int index)
{
    int size = 0;
    while (index < data.size())
    {
        if (data[index].substr(0, 4) == "$ ls")
        {
            cout << "hej";
        }
    }
    return size;
}

map<string, int> plotSizeToInt(vector<string> data)
{
    map<string, int> sizes; // plots dir name to size
    getSize(sizes, data, 0);
    return sizes;
}

/* Part 2 */

/* Main */
int main()
{
    const string FILENAME = "data.txt";
    // vector<string> data = readData(FILENAME);

    // plotSizeToInt(data);
}