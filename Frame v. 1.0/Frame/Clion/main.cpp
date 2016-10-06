#include <iostream>
#include <string>
#include <vector>
#include "Frame.h"
#include <bitset>
using namespace std;

int main()
{
    int x = 0;
    vector<int> rawData;
    rawData.push_back(0b0100);
    rawData.push_back(0b1100);
    rawData.push_back(0b1111);
    rawData.push_back(0b1101);
    rawData.push_back(0b0111);
    rawData.push_back(0b1110);
    rawData.push_back(0b1111);
    rawData.push_back(0b1101);
    Frame f(rawData);
    f.makeFrame();
    cout << "Frame genereret fra data: " << endl;
    for (int i = 0 ;i < f.getFrame().getLength();i++)
    {
        cout << bitset<4>(f.getFrame().getElement(i)) << endl;
    }

    Frame f1 = f.getFrame();
    cout << "Valider: " << f1.validataFrame() << endl;
    f1.unFrame();
    cout << "Data genereret fra frame: " << endl;
    for (int i = 0;i < f1.getFrame().getLength();i++)
    {
        cout << bitset<4>(f1.getFrame().getElement(i)) << endl;
    }





}