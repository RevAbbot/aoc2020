// basic file operations
#include <iostream>

#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

int main()
{
    int testSize = 5;
    double totald = 1.0;
    double numsd[] = {86.0, 187.0, 75.0, 89.0, 44.0};
    float totalf = 1.0;
    float numsf[] = {86.0, 187.0, 75.0, 89.0, 44.0};

    cout << "float min/max: " << numeric_limits<float>::min() << "/" << numeric_limits<float>::max() << endl;
    cout << "double min/max: " << numeric_limits<double>::min() << "/" << numeric_limits<double>::max() << endl;

    totald = totalf = 1.0;
    for (int i = 0; i < testSize; i++)
    {
        totalf = totalf * numsf[i];
        totald = totald * numsd[i];
    }
    cout << "Product 1 float: " << std::fixed << totalf << endl;
    cout << "Product 1 double: " << std::fixed << totald << endl;

    totalf = numsf[0];
    totald = numsd[0];
    for (int i = 1; i < testSize; i++)
    {
        totalf = totalf * numsf[i];
        totald = totald * numsd[i];
    }

    cout << "Product 2 float: " << std::fixed << totalf << endl;
    cout << "Product 2 double: " << std::fixed << totald << endl;

    cout << "Product 3: " << 86.0 * 187.0 * 75.0 * 89.0 * 44.0 << endl;
}