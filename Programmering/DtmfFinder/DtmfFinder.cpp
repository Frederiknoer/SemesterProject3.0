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

    int diffFactor = 150;
    double freqLow = 0;
    double freqSecLow = 0;
    double freqHigh = 0;
    double freqSecHigh = 0;
    int numberLow = 0;
    int numberSecLow = 0;
    int numberHigh = 0;
    int numberSecHigh = 0;
    int amplitudeFaktorH = 150;
    int amplitudeFaktorL = 150;
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

            //// Hvis de to værdier i Counter IKKE er ens, så er der sket en fejl ////

            if (DTMFCounter[0] != DTMFCounter[1])
            {
                /// Hvis der størrelsen af vores midlertidige buffer er lig 0, så slet den nye værdi ////

                if(tempDTMFCounter.size() != 0)
                {
                    if(DTMFCounter[1] == tempDTMFCounter[0])
                    {
                        DTMFCounter.erase(DTMFCounter.begin());

                        for (int i = 0; i < tempDTMFCounter.size(); ++i)
                        {
                            DTMFCounter.push_back(tempDTMFCounter[i]);
                        }

                        if(DTMFCounter.size() == 2)
                        {
                            DTMFbuffer.push_back(DTMFCounter[0]);
                        }

                        tempDTMFCounter.clear();

                    }else{
                        tempDTMFCounter.clear();
                        tempDTMFCounter.push_back(DTMFCounter[0]);
                        DTMFCounter.erase(DTMFCounter.begin());
                    }
                }else{
                    if (DTMFCounter[0] != DTMFCounter[1])
                    {
                        tempDTMFCounter.push_back(DTMFCounter[0]);
                        DTMFCounter.erase(DTMFCounter.begin());
                    }else{
                        tempDTMFCounter.clear();
                    }
                }

            }else{
                DTMFbuffer.push_back(DTMFCounter[0]);
                tempDTMFCounter.clear();
            }

        }

        //// Hvis DTMFcounter er større end 2, så tjek om de to nyeste værdier i counter er ens ////

        if (DTMFCounter.size() > 2) {

            ///// Hvis den nyeste og næstnyeste værdi IKKE er ens, så kør følgende kode ////

            if ((DTMFCounter[DTMFCounter.size() - 2]) != (DTMFCounter[DTMFCounter.size() - 1])) {

                ///// Hvis den nyeste værdi og den 3. nyeste værdi er ens, så slet den imellem ////

                if(DTMFCounter[DTMFCounter.size() - 3] == DTMFCounter[DTMFCounter.size() - 1])
                {
                    DTMFCounter.erase(DTMFCounter.begin() + 1 );

                }else{
                    if((DTMFCounter[DTMFCounter.size() - 3]) == (DTMFCounter[DTMFCounter.size() - 2]))
                    {
                        for (int i = 0; i < DTMFCounter.size() - 1; ++i) {
                            tempDTMFCounter.push_back(DTMFCounter[i]);
                        }
                    }

                    nextDtmfTone = DTMFCounter[DTMFCounter.size() - 1];
                    DTMFCounter.clear();
                    DTMFCounter.push_back(nextDtmfTone);
                }

            } else {
                if (DTMFCounter.size() == 5 || DTMFCounter.size() == 8 || DTMFCounter.size() == 11 ||
                    DTMFCounter.size() == 14)
                {
                    //cout << DTMFCounter[DTMFCounter.size() - 1];
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
/*
    cout << "DTMF toner fundet: ";
    for (int m = 0; m < DTMFbuffer.size(); ++m) {
        cout << DTMFbuffer[m];
    }

    cout << endl;


    cout << "  DTMFcounter: ";
    for (int k = 0; k < DTMFCounter.size(); ++k) {
        cout << DTMFCounter[k];
    }

    cout << endl << "  - Temp counter: ";
    for (int l = 0; l < tempDTMFCounter.size(); ++l) {
        cout << tempDTMFCounter[l];
    }
    cout << endl << endl;
*/
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