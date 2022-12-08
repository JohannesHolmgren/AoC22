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

vector<vector<int>> getTreesHeight(vector<string> rows)
{
    // Get tree heights as a 2d-grid of ints
    vector<vector<int>> trees;
    for (int i = 0; i < rows.size(); i++)
    {
        vector<int> row;
        for (int j = 0; j < rows[i].length(); j++)
        {
            row.push_back(rows[i][j] - '0');
        }
        trees.push_back(row);
    }
    return trees;
}

set<pair<int, int>> getVisibleTrees(vector<vector<int>> trees)
{
    // Assuming square
    set<pair<int, int>> visible = {make_pair(0, 0)};
    visible.erase(make_pair(0, 0));

    for (int row = 0; row < trees.size(); row++)
    {
        int tallestRow = -1;
        int tallestCol = -1;
        for (int col = 0; col < trees[row].size(); col++)
        {
            if (trees[row][col] > tallestRow)
            {
                // visible
                visible.insert(make_pair(row, col));
                tallestRow = trees[row][col];
                // cout << "at " << row << ", " << col << endl;
            }
            if (trees[col][row] > tallestCol)
            {
                // visible
                visible.insert(make_pair(col, row));
                tallestCol = trees[col][row];
                // cout << "at " << row << ", " << col << endl;
            }
        }
        // Again but backwards
        tallestRow = -1;
        tallestCol = -1;
        for (int col = trees[row].size() - 1; col >= 0; col--)
        {
            if (trees[row][col] > tallestRow)
            {
                // visible
                visible.insert(make_pair(row, col));
                tallestRow = trees[row][col];
                // cout << "at " << row << ", " << col << endl;
            }
            if (trees[col][row] > tallestCol)
            {
                // visible
                visible.insert(make_pair(col, row));
                tallestCol = trees[col][row];
                // cout << "at " << row << ", " << col << endl;
            }
        }
    }
    return visible;
}

int getHighestScenicScore(vector<vector<int>> trees)
{
    map<pair<int, int>, int> scenicScore;
    // initialise scores to 1
    for (int row = 0; row < trees.size(); row++)
        for (int col = 0; col < trees.size(); col++)
            scenicScore[make_pair(row, col)] = 1;

    for (int r = 1; r < trees.size(); r++)
    {
        vector<int> row = trees[r];
        map<int, pair<int, int>> peaksRow;
        map<int, pair<int, int>> peaksCol;

        for (int c = 1; c < row.size(); c++)
        {
            int heightRow = row[c];
            int heightCol = trees[c][r];
            // no view at that direction. Last is a "peak"
            if (heightRow <= row[c - 1])
            {
                peaksRow[row[c - 1]] = make_pair(r, c - 1);
                // cout << "Anew peak: " << r << ", " << c - 1 << " : " << row[c - 1] << endl;
            }
            // Larger than last. Check which "peak" blocks the view
            else
            {
                bool hasFound = false;
                map<int, pair<int, int>>::iterator it;
                for (it = peaksRow.begin(); it != peaksRow.end(); it++)
                {
                    // found the blocking tree. Add distance between them
                    if (it->first >= heightRow)
                    {
                        scenicScore[make_pair(r, c)] *= (c - it->second.second);
                        hasFound = true;
                        // cout << "Added " << (c - it->second.second) << " to " << r << ", " << c << " " << it->second.second << endl;
                        break;
                    }
                }
                if (!hasFound)
                {
                    scenicScore[make_pair(r, c)] *= (c);
                    // cout << "added " << c << " to " << r << ", " << c << endl;
                }
            }
            if (heightCol <= trees[c - 1][r])
            {
                peaksCol[trees[c - 1][r]] = make_pair(c - 1, r);
                cout << "Bnew peak: " << c - 1 << ", " << r << " : " << trees[c - 1][r] << endl;
            }
            // Larger than last. Check which "peak" blocks the view
            else
            {
                bool hasFound = false;
                map<int, pair<int, int>>::iterator it;
                for (it = peaksCol.begin(); it != peaksCol.end(); it++)
                {
                    // found the blocking tree. Add distance between them
                    if (it->first >= heightCol)
                    {
                        scenicScore[make_pair(c, r)] *= (c - 1 - it->second.second);
                        hasFound = true;
                        cout << "Added " << (c - 1 - it->second.second) << " to " << c << ", " << r << endl;
                        break;
                    }
                }
                if (!hasFound)
                {
                    scenicScore[make_pair(c, r)] *= (r);
                    cout << "added " << r << " to " << c << ", " << r << endl;
                }
            }
        }
        // Same but backwards
        peaksRow.clear();
        peaksCol.clear();
        for (int c = row.size() - 2; c >= 0; c--)
        {
            int heightRow = row[c];
            int heightCol = trees[c][r];
            // no view at that direction. Last is a "peak"
            if (heightRow <= row[c + 1])
            {
                peaksRow[row[c + 1]] = make_pair(r, c + 1);
                // cout << "Cnew peak: " << r << ", " << c + 1 << " : " << row[c + 1] << endl;
            }
            // Larger than last. Check which "peak" blocks the view
            else
            {
                bool hasFound = false;
                map<int, pair<int, int>>::iterator it;
                for (it = peaksRow.begin(); it != peaksRow.end(); it++)
                {
                    // found the blocking tree. Add distance between them
                    if (it->first >= heightRow)
                    {
                        scenicScore[make_pair(r, c)] *= ((c + 1 - it->second.second) * -1);
                        hasFound = true;
                        // cout << "Added " << ((c + 1 - it->second.second) * -1) << " to " << r << ", " << c << endl;
                        break;
                    }
                }
                if (!hasFound)
                {
                    scenicScore[make_pair(r, c)] *= (row.size() - 1 - c);
                    // cout << "added " << (row.size() - 1 - c) << " to " << r << ", " << c << endl;
                }
            }
            // Col instead of row
            if (heightRow <= trees[c + 1][r])
            {
                peaksCol[trees[c + 1][r]] = make_pair(c + 1, r);
                cout << "Dnew peak: " << c + 1 << ", " << r << " : " << trees[c + 1][r] << endl;
            }
            // Larger than last. Check which "peak" blocks the view
            else
            {
                bool hasFound = false;
                map<int, pair<int, int>>::iterator it;
                for (it = peaksCol.begin(); it != peaksCol.end(); it++)
                {
                    // found the blocking tree. Add distance between them
                    if (it->first >= heightCol)
                    {
                        scenicScore[make_pair(c, r)] *= ((c - it->second.second) * -1);
                        hasFound = true;
                        cout << "Added " << (c - it->second.second) * -1 << " to " << c << ", " << r << " " << it->second.second << endl;
                        break;
                    }
                }
                if (!hasFound)
                {
                    scenicScore[make_pair(r, c)] *= (trees[c].size() - 1 - r);
                    cout << "added " << (trees[c].size() - r) << " to " << c << ", " << r << endl;
                }
            }
        }
    }

    // Find the highest scenic score
    int highestScore = 0;
    map<pair<int, int>, int>::iterator it;
    for (it = scenicScore.begin(); it != scenicScore.end(); it++)
    {
        if (it->second > highestScore)
            highestScore = it->second;
    }
    return highestScore;
}

int main()
{
    const string FILENAME = "data.txt";
    vector<string> rows = readData(FILENAME);
    vector<vector<int>> trees = getTreesHeight(rows);
    int nVisibleTrees = getVisibleTrees(trees).size();
    cout << "Part 1: " << nVisibleTrees << endl;
    cout << "Part 2: " << endl
         << getHighestScenicScore(trees) << endl;

    return 0;
}