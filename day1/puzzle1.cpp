// basic file operations
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    std::vector<int> input;
    int count = 0;
    int value;

    ifstream myfile;
    myfile.open("input.txt");

    while (myfile >> value)
    {
        input.push_back(value);
    }
    myfile.close();

    for (int i = 0; i < input.size() - 2; i++)
    {
        for (int j = i + 1; j < input.size() - 1; j++)
        {
            for (int k = j + 1; k < input.size(); k++)
            {
                if (input.at(i) + input.at(j) + input.at(k) == 2020)
                {
                    int result = (input.at(i) * input.at(j) * input.at(k));
                    cout << input.at(i) << " * " << input.at(j) << " * " << input.at(k) << " = " << result << endl;
                    return 0;
                }
            }
        }
    }
    cout << "Combination not found";
    return 0;
}