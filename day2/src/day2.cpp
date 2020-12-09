// basic file operations
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//#include "../include/pw.hpp"

using namespace std;

class pw
{

public:
    pw(int min, int max, char c, string text);

    int _min, _max;
    char _c;
    string _text;
};

pw::pw(int min, int max, char c, string text)
{
    _min = min;
    _max = max;
    _c = c;
    _text = text;
};

ifstream myfile;
vector<pw> passwords;

void parseLine(string inputLine)
{
    pw *localPw = new pw(0, 0, 'x', "");
    string s = inputLine;
    string s1, s2, s3;
    int min, max;
    char c;
    string text, token;
    size_t pos = 0;

    pos = s.find(" ");
    s1 = s.substr(0, pos);
    s.erase(0, pos + 1);

    pos = s.find(" ");
    s2 = s.substr(0, pos);
    s.erase(0, pos + 1);

    //cout << "(" << s1 << "),(" << s2 << "),(" << s3 << ")\n";

    localPw->_text = s3 = s;

    pos = s1.find("-");
    localPw->_min = stoi(s1.substr(0, pos));
    s1.erase(0, pos + 1);
    localPw->_max = stoi(s1);

    localPw->_c = s2.substr(0, 1).c_str()[0];

    passwords.push_back(*localPw);
}

void parseFile()
{
    string inputLine;
    myfile.open("passwords.txt");

    while (getline(myfile, inputLine))
    {
        parseLine(inputLine);
    }
    myfile.close();
}

bool isGood1(pw *password)
{
    int charCount = 0;
    for (int i = 0; i < password->_text.length(); i++)
    {
        charCount += password->_text.at(i) == password->_c ? 1 : 0;
    }
    return charCount >= password->_min && charCount <= password->_max ? true : false;
}

bool isGood2(pw *password)
{
    int min = password->_min;
    int max = password->_max;
    char c = password->_c;
    string text = password->_text;

    if (text.length() < min || text.length() < max)
    {
        return false;
    }

    return (text.at(min - 1) == c) != (text.at(max - 1) == c);
}

void processInput1()
{
    int goodCount = 0;
    for (auto &localPw : passwords)
    {
        if (isGood1(&localPw))
        {
            goodCount++;
            cout << "(" << (&localPw)->_min << "),(" << (&localPw)->_max << "),(" << (&localPw)->_c << "),(" << (&localPw)->_text << ")\n";
            cout << "Found " << goodCount << " good passwords." << endl;
        }
    }
}

void processInput2()
{
    int goodCount = 0;
    for (auto &localPw : passwords)
    {
        if (isGood2(&localPw))
        {
            goodCount++;
            cout << "(" << (&localPw)->_min << "),(" << (&localPw)->_max << "),(" << (&localPw)->_c << "),(" << (&localPw)->_text << ")\n";
            cout << "Found " << goodCount << " good passwords." << endl;
        }
    }
}

int main()
{
    parseFile();
    processInput2();
}
