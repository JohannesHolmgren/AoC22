#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>

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

vector<vector<int>> getTreesHeight(vector<string> rows) {
    // Get tree heights as a 2d-grid of ints
    vector<vector<int>> trees;
    for(int i = 0; i < rows.size(); i++) {
        vector<int> row;
        for(int j = 0; j < rows[i].length(); j++){
            row.push_back(rows[i][j] - '0');
        }
        trees.push_back(row);
    }
    return trees;
}

set<pair<int, int>> getVisibleTrees(vector<vector<int>> trees) {
    // Assuming square
    set<pair<int, int>> visible = {make_pair(0, 0)};
    visible.erase(make_pair(0, 0));

    for(int row=0; row < trees.size(); row++) {
        int tallestRow = -1;
        int tallestCol = -1;
        for(int col=0; col < trees[row].size(); col++) {
            if(trees[row][col] > tallestRow) {
                // visible
                visible.insert(make_pair(row, col));
                tallestRow = trees[row][col];
                // cout << "at " << row << ", " << col << endl;
            }
            if(trees[col][row] > tallestCol) {
                // visible
                visible.insert(make_pair(col, row));
                tallestCol = trees[col][row];
                // cout << "at " << row << ", " << col << endl;
            }
        }
        // Again but backwards
        tallestRow = -1;
        tallestCol = -1;
        for(int col=trees[row].size() - 1; col >= 0; col--) {
            if(trees[row][col] > tallestRow) {
                // visible
                visible.insert(make_pair(row, col));
                tallestRow = trees[row][col];
                // cout << "at " << row << ", " << col << endl;
            }
            if(trees[col][row] > tallestCol) {
                // visible
                visible.insert(make_pair(col, row));
                tallestCol = trees[col][row];
                // cout << "at " << row << ", " << col << endl;
            }
        }
    }
    return visible;
}


int main() {
    const string FILENAME = "data.txt";
    vector<string> rows = readData(FILENAME);
    vector<vector<int>> trees = getTreesHeight(rows);
    int nVisibleTrees = getVisibleTrees(trees).size();
    cout << "Part 1: " << nVisibleTrees << endl;
    return 0;
}