#include "../DtmfFinder/DtmfFinder.h"
#include <ctime>
#include <iostream>
#include <cstdlib>

using namespace std;

DtmfFinder::DtmfFinder(){

}

void DtmfFinder::findDtmfTones(vector<double> freqSpek) {

    int DTMFtable[4][4];

    DTMFtable[0][0] = 0;
    DTMFtable[0][1] = 1;
    DTMFtable[0][2] = 2;
    DTMFtable[0][3] = 3;
    DTMFtable[1][0] = 4;
    DTMFtable[1][1] = 5;
    DTMFtable[1][2] = 6;
    DTMFtable[1][3] = 7;
    DTMFtable[2][0] = 8;
    DTMFtable[2][1] = 9;
    DTMFtable[2][2] = 10;
    DTMFtable[2][3] = 11;
    DTMFtable[3][0] = 12;
    DTMFtable[3][1] = 13;
    DTMFtable[3][2] = 14;
    DTMFtable[3][3] = 15;

    if (timeOutCounter > 6) {
        DTMFbuffer.clear();
        DTMFCounter.clear();
        timeOutCounter = 0;
    }

    int diffFactor = 200;
    double freqLow = 0;
    double freqSecLow = 0;
    double freqHigh = 0;
    double freqSecHigh = 0;
    int numberLow = 0;
    int numberSecLow = 0;
    int numberHigh = 0;
    int numberSecHigh = 0;
    int amplitudeFaktorH = 175;
    int amplitudeFaktorL = 175;
    int nextDtmfTone = 0;

    for (int j = 0; j < 4; ++j) {
        if (freqSpek[j] > freqLow) {
            freqLow = freqSpek[j];
            numberLow = j;
        }
    }
    for (int j = 0; j < 4; ++j) {
        if (freqSpek[j] > freqLow && j != numberLow) {
            freqSecLow = freqSpek[j];
            numberSecLow = j;
        }
    }

    for (int i = 4; i < 8; ++i) {
        if (freqSpek[i] > freqHigh) {
            freqHigh = freqSpek[i];
            numberHigh = i;
        }
    }
    for (int i = 4; i < 8; ++i) {
        if (freqSpek[i] > freqHigh && i != numberHigh) {
            freqSecHigh = freqSpek[i];
            numberSecHigh = i;
        }
    }

    if (freqHigh > amplitudeFaktorH && freqLow > amplitudeFaktorL && freqHigh - freqSecHigh > diffFactor &&
            freqLow - freqSecLow > diffFactor)
    {
        timeOutCounter = 0;
        DTMFCounter.push_back(DTMFtable[numberLow][numberHigh - 4]);

        //// Hvis DTMFcounter = 2, så tjek om de er lig med hinanden eller ej /////
        /// Hvis lig med hinanden så gem værdien, ellers slet værdien /////

        if (DTMFCounter.size() == 2) {
            if (DTMFCounter[0] != DTMFCounter[1])
            {
                DTMFCounter.erase(DTMFCounter.begin());
            }else {
                DTMFbuffer.push_back(DTMFCounter[0]);
            }
        }

        //// Hvis DTMFcounter er større end 2, så tjek om de to nyeste værdier i counter er ens ////

        if (DTMFCounter.size() > 2) {
            if ((DTMFCounter[DTMFCounter.size() - 2]) != (DTMFCounter[DTMFCounter.size() - 1])) {
                nextDtmfTone = DTMFCounter[DTMFCounter.size() - 1];
                DTMFCounter.clear();
                DTMFCounter.push_back(nextDtmfTone);

            } else {
                if (DTMFCounter.size() == 5 || DTMFCounter.size() == 8 || DTMFCounter.size() == 11 ||
                    DTMFCounter.size() == 14)
                {
                    DTMFbuffer.push_back(DTMFCounter[DTMFCounter.size() - 1]);

                    if(DTMFCounter.size() > 14)
                    {
                        cout << "DTMFcounter size excided it's max" << endl;
                    }
                }
            }
        }
    } else {
        timeOutCounter++;
    }



}

bool DtmfFinder::pairFinder(vector<int> dtmfVec)
{
    int pairCheck = 0;
    for (int l = 1; l < dtmfVec.size(); l++)
    {
        if (dtmfVec[l - 1] == 7 && dtmfVec[l] == 14)
            pairCheck++;
        if (pairCheck == 2 || pairCheck == 4 || pairCheck == 6)
        {
            return true;
        }
    }
    return false;
}

vector<int> DtmfFinder::getDTMFBuffer() {
    return DTMFbuffer;
}

void DtmfFinder::clearDTMFbuffer() {
    DTMFbuffer.clear();
    DTMFCounter.clear();
}

vector< vector<int> > DtmfFinder::pairGetter(vector<int> inData)
{
    vector<int> dataBuffer;
    for (int i = 1; i < inData.size(); i++)
    {
        if (inData[i - 1] == 7 && inData[i] == 14) //Start byte fundet
        {
            dataBuffer.push_back(inData[i - 1]);
            dataBuffer.push_back(inData[i]);
            i++;
            for (int j = i; j < inData.size(); j++)
            {
                dataBuffer.push_back(inData[j]);
                if (inData[j - 1] == 7 && inData[j] == 14)
                {
                    i = j + 1;
                    finalData.push_back(dataBuffer);
                    dataBuffer.clear();
                    break;
                }
            }
        }
    }
    return finalData;
}

void DtmfFinder::clearFinalData()
{
    finalData.clear();
}

DtmfFinder::~DtmfFinder()
{

}