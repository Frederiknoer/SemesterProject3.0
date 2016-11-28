#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Sound/sound.h"
#include "CustomRecorder/CustomRecorder.h"
#include "TextHandler/TextHandler.h"
#include "CSMAca/CSMAca/csmaCA.h"

using namespace std;

#define TWOPI = 6.283185                        //difinere 2 gange pi

int main()
{
    /*
    unsigned int recordSampleRate = 96000;      // sample rate
    unsigned int playSampleRate = 44100;        // play sample rate
    vector<sf::Int16> inputSamples;
     */
    string mystring;                            //opretter string
    vector<int> HexIntVec;
    vector<int> HexBuffer;                      //opretter HexBuffer
    vector<int> ID = { 14, 15 };                // computer ID
    vector<int> tagetID = { 10, 12 };           // taget ID
    CustomRecorder recorder;
    csmaCA csmaHandler(ID, tagetID);            //opretter handler (parametret ID bliver overskrevet senere)
    TextHandler myTest;                         //opretter texthandler objekt


    cout << "Skriv tekst: ";                                //beder om input
    getline(cin, mystring);                                 //gemmer input i mystring vektor


    HexIntVec = myTest.InputText(mystring);                 //konvatere input text til hex og gemmer i HexInVec
    for (int i = 0; i < (mystring.length() * 2); ++i)       //smider HexInVec ind i HexBuffer
    {
        HexBuffer.push_back(HexIntVec[i]);
    }

    if(csmaHandler.sendData(HexBuffer))                     //sender data. retunere true hvis data sendt korekt
        cout << "Main.cpp [main()]  -  Data sendt korekt!" << endl;
    else
        cout << "Main.cpp [main()]  -  Fejl! Data ikke sendt korekt" << endl;

    return 0;
}
