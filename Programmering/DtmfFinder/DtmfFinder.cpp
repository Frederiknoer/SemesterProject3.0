#include "../DtmfFinder/DtmfFinder.h"

#include <iostream>

using namespace std;

DtmfFinder::DtmfFinder(){

}

void DtmfFinder::findDtmfTones(vector<double> freqSpek){

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



    // Gennemsnit metoden

    double avg = 0;
    int counter = 0;
    double freqs[2];
    int numberConst[2];

    for (int i = 0; i < 8; ++i) {
        avg += freqSpek[i];
    }

    avg = avg / 8;




    for (int j = 0; j < 8; ++j)
    {
        if (((freqSpek[j]) > avg && avg > 200))
        {
            freqs[counter] = freqSpek[j];
            numberConst[counter] = j;
            counter++;
        }
    }


    if(counter == 2) {
        if (numberConst[0] < 4 && numberConst[0] >= 0 && numberConst[1] > 3 && numberConst[1] <=7)
        {
            DTMFCounter.push_back(DTMFtable[numberConst[0]] [numberConst[1]-4]);

            if(DTMFCounter.size() == 1)
            {
             //   cout << DTMFCounter[0];
                DTMFbuffer.push_back(DTMFCounter[0]);

            }

            if(DTMFCounter.size() > 1)
            {
                if((DTMFCounter[DTMFCounter.size()-2]) != (DTMFCounter[DTMFCounter.size()-1]))
                {

                  //  cout << DTMFCounter[DTMFCounter.size()-1];
                    DTMFbuffer.push_back(DTMFCounter.size()-1);

                    DTMFCounter.clear();

                    DTMFCounter.push_back(DTMFtable[numberConst[0]] [numberConst[1]-4]);
                }else{
                    if (DTMFCounter.size() == 3)
                    {
                      //  cout << DTMFCounter[DTMFCounter.size()-1];
                        DTMFbuffer.push_back(DTMFCounter.size()-1);
                    }

                    if(DTMFCounter.size() == 6)
                    {
                       // cout << DTMFCounter[DTMFCounter.size()-1];
                        DTMFbuffer.push_back(DTMFCounter.size()-1);
                    }
                }



            }
        }
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

DtmfFinder::~DtmfFinder()
{

}