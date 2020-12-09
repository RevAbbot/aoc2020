// basic file operations
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>

using namespace std;

ifstream myfile;

class bagRule
{
public:
    bagRule();
    string _name;
    map<string, int> _contains;
    bool _checked;

    void insert(string bagName, int count);
};

bagRule::bagRule(){};

void bagRule::insert(string bagName, int count)
{
    _contains.insert(std::pair<string, int>(bagName, count));
}

vector<bagRule> bagRules;

const string myBag = "shiny gold";

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

string level = "";

int countContains(string bagName, const int level)
{
    int count = 0;
    bagRule br;
    map<string, int>::iterator it;
    string indent = "                                                                                                  ";

    cout << "* Checking for bags that can contain " << bagName << endl;

    for (int b = 0; b < bagRules.size(); b++)
    {
        br = bagRules.at(b);
        it = br._contains.begin();
        if (br._checked == false)
        {
            while (it != br._contains.end())
            {
                if (it->first == bagName)
                {
                    bagRules.at(b)._checked = true;
                    count++;
                    cout << indent.substr(0, level) << count << ": " << br._name << " << " << bagName << endl;
                    count += countContains(br._name, level + 1);
                    //checkedBags.push_back(br._name);
                    break;
                }
                it++;
            }
        }
    }

    return count;
}

int mustContain(string bagName, const int level)
{
    int count = 0;
    bagRule br;
    map<string, int>::iterator it;
    string indent = "                                                                                                  ";

    cout << "* Checking bags that " << bagName << " must contain" << endl;

    for (int b = 0; b < bagRules.size(); b++)
    {
        br = bagRules.at(b);
        if (br._name == bagName)
        {
            it = br._contains.begin();
            while (it != br._contains.end())
            {
                cout << indent.substr(0, level) << bagName << " contains " << it->second << " " << it->first << endl;
                count += it->second + it->second * mustContain(it->first, level + 1);
                it++;
            }
        }
    }
    return count;
}

void processInput1()
{
    int count = countContains(myBag, 0);
    cout << "Combinations to contain " << myBag << ": " << count << endl;
    cout.flush();
}
void processInput2()
{
    int count = mustContain(myBag, 0);
    cout << "My " << myBag << " bag: " << count << endl;
    cout.flush();
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
    vector<string> tokens;
    bagRule *br;

    tokens = split(inputLine, ' ');
    br = new bagRule();
    br->_checked = false;
    br->_name = tokens.at(0) + ' ' + tokens.at(1);
    if (tokens.size() > 7)
    {
        for (int t = 4; t < tokens.size(); t += 4)
        {
            br->insert(tokens.at(t + 1) + ' ' + tokens.at(t + 2), stoi(tokens.at(t)));
        }
    }
    bagRules.push_back(*br);

    //cout << "INPUTLINE: \"" << inputLine << "\"" << endl;
}

void printBagRules()
{
    for (int b = 0; b < bagRules.size(); b++)
    {
        bagRule br = bagRules.at(b);
        map<string, int>::iterator it = br._contains.begin();
        cout << "Bag " << b << ": " << br._name << endl;
        while (it != br._contains.end())
        {
            cout << "   " << it->second << " " << it->first << endl;
            it++;
        }
    }
}

void parseFile()
{
    string inputLine = "";
    myfile.open("bags.txt");

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
    processInput2();
}
