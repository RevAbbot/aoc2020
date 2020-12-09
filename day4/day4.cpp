// basic file operations
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>

using namespace std;

ifstream myfile;
typedef map<string, string> passportMap;
typedef passportMap::iterator passportMapIterator;
vector<passportMap> passPorts;

int passportCount = 0;

void printMap(passportMap p)
{
    passportMapIterator it = p.begin();

    while (it != p.end())
    {
        cout << it->first << ":" << it->second << " ";
        it++;
    }
    cout << endl;
}

bool isValidField(string k, string v, int pairCount)
{
    bool answer = false;

    if (k.compare("byr") == 0)
    {
        int y = stoi(v);
        answer = (y > 1919) && (y < 2003);
        //cout << "byr: \"" << y << "\" " << answer << " ";
    }

    if (k.compare("iyr") == 0)
    {
        int y = stoi(v);
        answer = y > 2009 && y < 2021;
    }

    if (k.compare("eyr") == 0)
    {
        int y = stoi(v);
        answer = y > 2019 && y < 2031;
    }

    if (k.compare("hgt") == 0)
    {
        int y = stoi(v);
        if (v.find("cm") != string::npos)
        {
            answer = y > 149 && y < 194;
        }
        else
        {
            if (v.find("in") != string::npos)
            {
                answer = y > 58 && y < 77;
            }
        }
    }

    if (k.compare("hcl") == 0)
    {
        answer = v.compare(0, 1, "#") == 0 && v.size() == 7 && v.find_first_not_of("0123456789abcdefABCDEF", 1) == std::string::npos;
    }

    if (k.compare("ecl") == 0)
    {
        string colors = "amb blu brn gry grn hzl oth";
        answer = v.size() == 3 && (colors.find(v, 0) % 4 == 0);
    }

    if (k.compare("pid") == 0)
    {
        answer = v.size() == 9 && v.find_first_not_of("0123456789", 0) == std::string::npos;
    }

    if (k.compare("cid") == 0)
    {
        answer = pairCount == 8;
    }

    return answer;
}

bool isValidPassport(passportMap p)
{
    passportMapIterator it = p.begin();
    int pairCount = p.size();
    bool answer = true;
    bool validField = true;

    if (pairCount < 7)
    {
        answer = false; // too few fields
        cout << "FAIL: ";
    }
    else
    {
        while (it != p.end())
        {
            validField = isValidField(it->first, it->second, pairCount);
            if (validField == false)
            {
                answer = false;
                cout << "FAIL: " << it->first << ":" << it->second << " ";
                break;
            }
            it++;
        }
    }

    cout << pairCount << " - ";
    printMap(p);

    return answer;
}

void processInput1()
{
    int goodCount = 0;

    for (int i = 0; i < passPorts.size(); i++)
    {
        goodCount += isValidPassport(passPorts.at(i)) ? 1 : 0;
    }

    cout << "Valid passports: " << goodCount << "/" << passPorts.size() << endl;
}

void parseLine(string inputLine)
{
    string pair, key, val;
    int pos = 0;
    int index = 0;
    string str = inputLine;
    passportMap localMap;

    // Split line into k:v pairs separated by spaces
    passportCount++;

    do
    {
        //cout << "str: \"" << str << "\"" << endl;
        index = str.find(" ");
        if (index == string::npos)
        {
            passPorts.push_back(localMap);
            break;
        }

        pair = str.substr(0, index);
        //cout << "\"" << pair << "\"" << endl;
        key = pair.substr(pos, 3);
        val = pair.substr(pos + 4);
        localMap.insert(std::make_pair(key, val));
        //cout << "key: " << key << ", val: " << val << endl;
        str = str.substr(index + 1);

    } while (true);

    //cout << "Passport #" << passportCount << ": " << passPorts.at(passportCount - 1).size() << " pairs." << endl;
}

void parseFile()
{
    string inputLine = "";
    string inputString = "";
    myfile.open("passports.txt");

    do // combine multple file lines into a single passport definition string
    {
        getline(myfile, inputLine);
        //cout << "INPUTLINE: \"" << inputLine << "\"" << endl;

        if (inputLine.length() == 0)
        {
            // cout << "PASSPORTSTRING: \"" << inputString << "\"" << endl;

            parseLine(inputString);
            inputString = "";
        }
        else
        {
            inputString += inputLine + " ";
        }
    } while (!myfile.eof());

    myfile.close();
}

int main()
{
    parseFile();
    processInput1();
}
