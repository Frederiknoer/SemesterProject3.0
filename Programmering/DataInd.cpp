#include <iostream>
#include <array>
using namespace std;

int main()
{
    char outDataString[10000];
    int outputBuffer[10000];

    cin.getline(outDataString, 10000);
    std::string str(outDataString);

    for (int i = 0; i < str.length(); i++)
    {
        unsigned char ucOutCharacter = outDataString[i];
        outputBuffer[i] = (unsigned int)ucOutCharacter;
    }

    for (int i = 0; i < str.length(); i++)
    {
        cout << outputBuffer[i] << endl;
    }
    return 0;
}