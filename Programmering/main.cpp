
#include <iostream>
#include <SFML/Audio.hpp>
#include "CustomRecorder/CustomRecorder.h"
#include "CSMAca/CSMAca/csmaCA.h"

using namespace std;

#define TWOPI = 6.283185                        //difinere 2 gange pi

int main()
{
    double recordSampleRate = 4096; // IKKE RØR!
    double playSampleRate = 44100;
    double samplesPrDTF = 60;
    int windowSize = 3;
    int samplePlayTime = (int)(samplesPrDTF * windowSize);

    //=========== INIT ==============
    vector<vector<int> > pakkeV;    //opretter Test pakke
    pakkeV.push_back({6, 8, 6, 5}); //tilføjer 4 pakke elementer
    pakkeV.push_back({6, 5, 6, 5});
    pakkeV.push_back({6, 5, 6, 10});
    pakkeV.push_back({1, 15, 1, 15}); // <-- "pakke stop" element

    vector<int> ID = { 14, 15 };                // computer ID
    vector<int> tagetID = { 10, 12 };           // taget ID
    csmaCA csmaHandler(ID, tagetID);            //opretter handler (parametret ID bliver overskrevet senere)
    csmaCA * csmaPointer = 0;                   //initalisere nul pointer til csmaHandler
    csmaCA * pointerHolder = 0;
    csmaPointer = &csmaHandler;                 //binder opinter til csmaHandler
    CustomRecorder recorder(csmaPointer);       //opretter costum recorder objekt
    recorder.setSamplesPrDFT(samplesPrDTF);
    recorder.start(recordSampleRate);                      //starter recorder med samplingrate på 44100Hz
    string myString;                            //holder bruger input

    //===============================
    int hej;
    cin >> hej;

//    while(true)
 //   {
        cout << "skriv besked: ";
        getline(cin, myString);
        //frede pakke handler
        if(csmaHandler.sendPakker(pakkeV))                         //sender data. retunere true hvis data sendt korekt
            cout << "Main.cpp [main()]  -  alle pakker sendt korekt!" << endl;
        else
            cout << "Main.cpp [main()]  -  Fejl! alle pakker kunne ikke sendes.. anal rytter!" << endl;
 //   }



    if(csmaHandler.sendData({}))
        cout << "main.cpp [min()]  -  Fejl! program har escaped while(true) loop..." << endl;
    return 0;
}