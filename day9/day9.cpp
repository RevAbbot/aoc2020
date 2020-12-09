// basic file operations
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>

#define PREAMBLE_SIZE (25)

using namespace std;

ifstream myfile;

vector<double> xmas;
int invalidIndex = 0;

bool isValid(int index)
{
    double test = xmas.at(index);
    for (int i = index - PREAMBLE_SIZE; i < index; i++)
    {
        for (int j = i + 1; j < index; j++)
        {
            if (xmas.at(i) + xmas.at(j) == test)
            {
                return true;
            }
        }
    }
    return false;
}

void processInput1()
{
    for (int index = PREAMBLE_SIZE; index < xmas.size(); index++)
    {
        if (!isValid(index))
        {
            invalidIndex = index;
            cout << std::setprecision(10) << "First invalid number: " << xmas.at(index) << " at index " << index << endl;
            break;
        }
    }
}

double sumOf(int lowIndex, int highIndex)
{
    double answer = 0;

    for (int i = lowIndex; i < highIndex; i++)
    {
        answer += xmas.at(i);
    }
    return answer;
}

void processInput2()
{
    int start = invalidIndex;
    int end = start;
    double sum;

    double invalidValue = xmas.at(invalidIndex);

    while (start > 0)
    {
        while (end >= 0)
        {
            end--;
            sum = sumOf(end, start);
            if (sum == invalidValue)
            {
                double answer;
                double mn = xmas.at(end);
                double mx = mn;
                for (int k = end; k < start; k++)
                {
                    double temp = xmas.at(k);
                    mn = temp < mn ? temp : mn;
                    mx = temp > mx ? temp : mx;
                }
                answer = mn + mx;
                cout << "Range (" << end << "-" << start << "):(" << mn << " + " << mx << ") = " << answer << endl;
                return;
            }
            else if (sum > invalidValue)
            {
                start--;
                end = start;
                break;
            }
        }
    }
}

vector<string> split(const string &s, char d)
{
    vector<string> answer;
    stringstream ss(s);
    string token;

    while (getline(ss, token, d))
    {
        answer.push_back(token);
    }

    return answer;
}

void parseLine(string inputLine)
{
    xmas.push_back(stod(inputLine));
    //cout << "INPUTLINE: \"" << inputLine << "\"" << endl;
}

void parseFile()
{
    string inputLine = "";
    myfile.open("encrypt.txt");

    while (!myfile.eof())
    {
        getline(myfile, inputLine);
        parseLine(inputLine);
    };

    myfile.close();
    //  printBagRules();
}

void initialize()
{
}

int main()
{
    initialize();
    parseFile();
    processInput1();
    processInput2();
}
