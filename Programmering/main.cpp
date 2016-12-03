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
    //=========== INIT ==============
    vector<vector<int> > pakkeV;    //opretter Test pakke
    pakkeV.push_back({1, 1, 1, 1}); //tilføjer 4 pakke elementer
    pakkeV.push_back({2, 2, 2, 2});
    pakkeV.push_back({3, 3, 3, 3});
    pakkeV.push_back({0, 0, 0, 0}); // <-- "pakke stop" element

    vector<int> ID = { 14, 15 };                // computer ID
    vector<int> tagetID = { 10, 12 };           // taget ID
    csmaCA csmaHandler(ID, tagetID);            //opretter handler (parametret ID bliver overskrevet senere)
    csmaCA * csmaPointer = 0;                   //initalisere nul pointer til csmaHandler
    csmaCA * pointerHolder = 0;
    csmaPointer = &csmaHandler;                 //binder opinter til csmaHandler
    CustomRecorder recorder(csmaPointer);       //opretter costum recorder objekt
    recorder.start(44100);                      //starter recorder med samplingrate på 44100Hz
    string myString;                            //holder bruger input

    //===============================

    while(true)
    {
        cout << "skriv besked: ";
        getline(cin, myString);
        //frede pakke handler
        if(csmaHandler.sendPakker(pakkeV))                         //sender data. retunere true hvis data sendt korekt
            cout << "Main.cpp [main()]  -  alle pakker sendt korekt!" << endl;
        else
            cout << "Main.cpp [main()]  -  Fejl! alle pakker kunne ikke sendes.. anal rytter!" << endl;
    }
    cout << "main.cpp [min()]  -  Fejl! program har escaped while(true) loop..." << endl;
    return 0;
}