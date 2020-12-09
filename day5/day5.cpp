// basic file operations
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>

using namespace std;

ifstream myfile;
vector<string> boardingPasses;
vector<int> rows;
vector<int> cols;
vector<int> seatIDs;
int maxSeatID = 0;

int rowOf(string s)
{
    int min = 0;
    int max = 127;
    int row = 0;

    //  cout << s << ": " << endl;

    for (int i = 0; i < 7; i++)
    {
        if (s.at(i) == 'F')
        {
            max = (min + max) / 2;
            row = min;
        }
        else
        {
            min = ((min + max) / 2) + 1;
            row = max;
        }
        //     cout << s.at(i) << " " << min << " " << max << " " << row << " | ";
    }
    //  cout << endl;
    return row;
}

int colOf(string s)
{
    int min = 0;
    int max = 7;
    int col = 0;

    // cout << s << ": " << endl;

    for (int i = 7; i < s.length(); i++)
    {
        if (s.at(i) == 'L')
        {
            max = (min + max) / 2;
            col = min;
        }
        else
        {
            min = ((min + max) / 2) + 1;
            col = max;
        }
        //    cout << s.at(i) << " " << min << " " << max << " " << col << " | ";
    }
    //cout << endl;
    return col;
}

int seatIDOf(int r, int c)
{
    return (8 * r) + c;
}

void showMissingSeats()
{
    bool found = false;
    int seatID;

    for (int r = 0; r < 128; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            found = false;
            seatID = seatIDOf(r, c);
            for (int i = 0; i < seatIDs.size(); i++)
            {
                if (seatID == seatIDs.at(i) || seatID > maxSeatID)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Missing: " << seatID << endl;
        }
    }
}

void processInput1()
{
    int seatID = 0;

    for (int i = 0; i < boardingPasses.size(); i++)
    {
        rows.push_back(rowOf(boardingPasses.at(i)));
        cols.push_back(colOf(boardingPasses.at(i)));
        seatID = seatIDOf(rows.at(i), cols.at(i));
        maxSeatID = max(maxSeatID, seatID);
        seatIDs.push_back(seatID);
        //  cout << boardingPasses.at(i) << " " << rows.at(i) << " " << cols.at(i) << " " << seatID << endl;
    }
    cout << "Max seatID: " << maxSeatID << endl;

    showMissingSeats();
}

void parseLine(string inputLine)
{
    boardingPasses.push_back(inputLine);
}

void parseFile()
{
    string inputLine;
    myfile.open("boardingPasses.txt");

    while (getline(myfile, inputLine))
    {
        parseLine(inputLine);
    }
    myfile.close();
}

void initialize()
{
}

int main()
{
    initialize();
    parseFile();
    processInput1();
}
