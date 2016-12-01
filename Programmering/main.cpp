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

    csmaCA csmaHandler(ID, tagetID);            //opretter handler (parametret ID bliver overskrevet senere)
    csmaCA * csmaPointer = 0;                   //initalisere nul pointer til csmaHandler
    csmaPointer = &csmaHandler;                 //binder opinter til csmaHandler

    TextHandler myTest;                                         //opretter texthandler objekt

    //CustomRecorder recorder(csmaHandler);                      //opretter costum recorder objekt
    CustomRecorder recorder(csmaPointer);                       //opretter costum recorder objekt

    recorder.start(44100);                                      //starter recorder med samplingrate på 44100Hz


    //cout << "Skriv tekst: ";                                //beder om input
    //getline(cin, mystring);                                 //gemmer input i mystring vektor
    vector<vector<int> > pakkeV;
    pakkeV.push_back({1, 1, 1, 1}); //tilføjer 4 pakker
    pakkeV.push_back({2, 2, 2, 2});
    pakkeV.push_back({3, 3, 3, 3});
    pakkeV.push_back({0, 0, 0, 0}); // <-- pakke stop

    cout << "pakkeV.size() = " << pakkeV.size() << endl;

    if(csmaHandler.sendPakker(pakkeV))                     //sender data. retunere true hvis data sendt korekt
        cout << "Main.cpp [main()]  -  alle pakker sendt korekt!" << endl;
    else
        cout << "Main.cpp [main()]  -  Fejl! alle pakker kunne ikke sendes.. anal rytter!" << endl;

    return 0;
}
