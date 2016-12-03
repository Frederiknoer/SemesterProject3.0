#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Sound/sound.h"
#include "CustomRecorder/CustomRecorder.h"
<<<<<<< HEAD
#include "TextHandler/TextHandler.h"
#include "CSMAca/CSMAca/csmaCA.h"

=======
#include <time.h>
>>>>>>> windowsTestEnvironment
using namespace std;

#define TWOPI = 6.283185                        //difinere 2 gange pi

int main()
{
<<<<<<< HEAD
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

    TextHandler myTest;                                         //opretter texthandler objekt
    CustomRecorder recorder(csmaHandler);                       //opretter costum recorder objekt
    recorder.start(44100);

    cout << "Skriv tekst: ";                                //beder om input
    getline(cin, mystring);                                 //gemmer input i mystring vektor


    HexIntVec = myTest.InputText(mystring);                 //konvatere input text til hex og gemmer i HexInVec
    for (int i = 0; i < (mystring.length() * 2); ++i)       //smider HexInVec ind i HexBuffer
    {
=======
    double recordSampleRate = 4096; // IKKE RØR!
    double playSampleRate = 44100;
    double samplesPrDTF = 60;
    int windowSize = 3;
    int samplePlayTime = (int)(samplesPrDTF * windowSize);


    Sound mySound;
    mySound.setSamplingRate(playSampleRate);
    mySound.setSamplePrTone(samplePlayTime);

    CustomRecorder recorder;
    recorder.start((unsigned int)recordSampleRate);
    recorder.setSamplesPrDFT((int)samplesPrDTF);

    /*vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};


    mySound.makeSound(input);
    vector<sf::Int16> inputSamples = mySound.getSound();

    sf::SoundBuffer bufferInput;
    bufferInput.loadFromSamples(&inputSamples[0], inputSamples.size(), 1, playSampleRate);

    sf::Sound sound;
    sound.setBuffer(bufferInput);
    sound.play();

    mySound.delay(input.size() * 44 + 350);*/


    string mystring;
    cout << "Skriv tekst: ";
    getline(cin, mystring);


while (1) {
    vector<int> HexBuffer;

    TextHandler myTest;
    vector<int> HexIntVec = myTest.InputText(mystring);

    for (int i = 0; i < (mystring.length() * 2); ++i) {
>>>>>>> windowsTestEnvironment
        HexBuffer.push_back(HexIntVec[i]);
    }

    if(csmaHandler.sendData(HexBuffer))                     //sender data. retunere true hvis data sendt korekt
        cout << "Main.cpp [main()]  -  Data sendt korekt!" << endl;
    else
        cout << "Main.cpp [main()]  -  Fejl! Data ikke sendt korekt" << endl;

<<<<<<< HEAD

=======
    vector<int> frammedHex = framming.getFrame();
    for (int j = 0; j < frammedHex.size(); ++j) {
        cout << frammedHex[j];
    }
    cout << endl;


    mySound.makeSound(frammedHex);

    vector<sf::Int16> inputSamples = mySound.getSound();

    sf::SoundBuffer bufferInput;
    bufferInput.loadFromSamples(&inputSamples[0], inputSamples.size(), 1, playSampleRate);

    sf::Sound sound;
    sound.setBuffer(bufferInput);
    sound.play();



    HexBuffer.clear();
    HexIntVec.clear();

    getline(cin, mystring);
}


>>>>>>> windowsTestEnvironment

    return 0;
}
