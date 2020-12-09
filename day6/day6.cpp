// basic file operations
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>

using namespace std;

ifstream myfile;
typedef vector<string> group;
vector<group> groups;
const string qCode = "abcdefghijklmnopqrstuvwxyz";
const string qCodeEmpty = "                          ";

int count(string s, char c)
{
    // Count variable
    int res = 0;

    for (int i = 0; i < s.length(); i++)

        // checking character in string
        if (s[i] == c)
            res++;

    return res;
}

void processInput1()
{
    string qMap = qCodeEmpty;
    string person;
    int groupCount = 0;
    int sumOfGroupQs = 0;
    group thisGroup;
    bool groupAnswered = true;
    int sumOfAllGroupQs = 0;
    int agreeCount = 0;

    for (int g = 0; g < groups.size(); g++)
    {
        groupCount = 0;
        qMap = qCodeEmpty;
        thisGroup = groups.at(g);

        for (int p = 0; p < thisGroup.size(); p++)
        {
            person = groups.at(g).at(p);
            for (int c = 0; c < person.length(); c++)
            {
                qMap.at(person.at(c) - 'a') = person.at(c);
            }
            //cout << "G" << g << "P" << p << ": " << qMap << endl;
        }
        groupCount = qMap.length() - count(qMap, ' ');
        //    cout << "G" << g << " sum: " << groupCount;
        sumOfGroupQs += groupCount;
    }

    cout << "Group total - any question: " << sumOfGroupQs << endl;

    for (int g = 0; g < groups.size(); g++)
    {
        groupCount = 0;
        agreeCount = 0;
        thisGroup = groups.at(g);
        for (int q = 0; q < qCode.length(); q++)
        {
            groupAnswered = true;
            for (int p = 0; p < thisGroup.size(); p++)
            {
                person = thisGroup.at(p);
                if (person.find(qCode.at(q)) == string::npos)
                {
                    groupAnswered = false;
                    break;
                }
            }
            agreeCount += groupAnswered ? 1 : 0;
        }
        groupCount += agreeCount;

        cout << "G" << g << " sum: " << groupCount << endl;
        sumOfAllGroupQs += groupCount;
    }
    cout << "Group total: " << sumOfAllGroupQs << endl;
}

void parseLine(string inputLine)
{
}

void addPerson(int groupIndex, string answers)
{
    vector<string> temp;

    // cout << "Adding " << answers << " to group " << groupIndex << endl;
    if (groups.size() < groupIndex + 1)
    {
        groups.push_back(temp);
    }
    groups.at(groupIndex).push_back(answers);
}

void parseFile()
{
    int groupCount = 0;
    string inputLine = "";
    myfile.open("questionare.txt");

    while (!myfile.eof())
    {

        getline(myfile, inputLine);

        //cout << "INPUTLINE: \"" << inputLine << "\"" << endl;
        if (inputLine.length() == 0)
        {
            groupCount++;
        }
        else
        {
            addPerson(groupCount, inputLine);
        }
    };

    myfile.close();

    //    for (int i = 0; i < groups.size(); i++)
    //    {
    //        for (int p = 0; p < groups.at(i).size(); p++)
    //        {
    //            cout << "G" << i << " P" << p << ": " << groups.at(i).at(p) << endl;
    //        }
    //    }
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
