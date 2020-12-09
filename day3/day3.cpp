// basic file operations
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

#define TREE ('#')
#define OPEN ('.')

using namespace std;

ifstream myfile;
vector<string> forest;

char isTree(int row, int col)
{
    int numCols = forest.at(0).length();

    char c = forest.at(row).at(col % numCols);

    //cout << "(" << row << ", " << col << "): " << c << endl;
    return c == TREE;
}

void parseLine(string inputLine)
{
    forest.push_back(inputLine);
}

void parseFile()
{
    string inputLine;
    myfile.open("trees.txt");

    while (getline(myfile, inputLine))
    {
        parseLine(inputLine);
    }
    myfile.close();
}

void processInput1()
{
    int cRow = 0;
    int cCol = 0;
    int cRows[] = {1, 1, 1, 1, 2};
    int cCols[] = {1, 3, 5, 7, 1};
    int testSize = sizeof(cCols) / sizeof(cCols[0]);
    float treeCounts[testSize];
    int lastRow = forest.size() - 1;
    float totalTrees = 1.0;

    for (int i = 0; i < testSize; i++)
    {
        cRow = cCol = 0;
        treeCounts[i] = 0.0;
        while (cRow < lastRow)
        {
            cRow += cRows[i];
            cCol += cCols[i];

            treeCounts[i] += isTree(cRow, cCol) ? 1.0 : 0.0;
            //cout << std::setprecision(0) << "Treecount: " << treeCounts[i] << endl;
        }
        cout << "Using (" << cRows[i] << ", " << cCols[i] << "): " << std::fixed << treeCounts[i] << " trees." << endl;

        totalTrees = totalTrees * treeCounts[i];
        cout << "Cumulative product of treecounts: " << std::fixed << totalTrees << endl;
    }

    totalTrees = treeCounts[0];
    for (int i = 1; i < testSize; i++)
    {
        totalTrees = totalTrees * (float)treeCounts[i];
    }
    cout << "Product of treecounts: " << std::fixed << totalTrees << endl;
    cout << 86.0 * 187.0 * 75.0 * 89.0 * 44.0 << endl;
}

int main()
{
    parseFile();
    processInput1();
}
