
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

    TextHandler textHandler;
    vector<int> ID = { 14, 15 };                // computer ID
    vector<int> tagetID = { 10, 12 };           // taget ID
    csmaCA csmaHandler(ID, tagetID);            //opretter handler (parametret ID bliver overskrevet senere)
    csmaCA * csmaPointer = 0;                   //initalisere nul pointer til csmaHandler
    csmaCA * pointerHolder = 0;
    csmaPointer = &csmaHandler;                 //binder opinter til csmaHandler
    CustomRecorder recorder(csmaPointer);       //opretter costum recorder objekt
    recorder.setSamplesPrDFT(samplesPrDTF);
    recorder.start(recordSampleRate);           //starter recorder med samplingrate på 44100Hz
    string myString;                            //holder bruger input

    //=========== Send packages ==============
    cout << "skriv besked: ";
    getline(cin, myString);
    vector <vector<int> > packages = textHandler.textSplitter(textHandler.InputText(myString));
    csmaHandler.sendPakker(packages);
    //========================================

    return 0;
}