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

class instruction
{
public:
    instruction(string op, int arg);
    string _op;
    int _arg;
    int _hitCount;
};

instruction::instruction(string op, int arg)
{
    _op = op;
    _arg = arg;
    _hitCount = 0;
};

vector<instruction> code;
int accumulator = 0;

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
    int pc = 0;
    int prevPc = 0;
    instruction in = code.at(pc);

    while (!in._hitCount)
    {
        code.at(pc)._hitCount++;
        prevPc = pc;

        cout << pc << ": " << in._op << " " << in._arg << " (" << accumulator << ")" << endl;

        switch (in._op.front())
        {
        case 'a':
            accumulator += in._arg;
            pc++;
            break;

        case 'j':
            pc += in._arg;
            break;

        case 'n':
            pc++;
            break;
        }
        in = code.at(pc);
    }

    cout << "Accumulator: " << accumulator << " at instruction " << prevPc << endl;
}

void processInput2()
{
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
    instruction *in;
    vector<string> tokens;

    tokens = split(inputLine, ' ');

    in = new instruction(tokens.at(0), stoi(tokens.at(1)));
    //   cout << "Adding: " << in->_op << " " << in->_arg << endl;
    code.push_back(*in);
    *in = code.back();
    //   cout << "Verifying: " << in->_op << " " << in->_arg << endl;

    //cout << "INPUTLINE: \"" << inputLine << "\"" << endl;
}

void parseFile()
{
    string inputLine = "";
    myfile.open("asycode.txt");

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
}
