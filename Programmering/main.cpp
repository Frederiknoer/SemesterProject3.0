#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Sound/sound.h"
#include "CustomRecorder/CustomRecorder.h"
#include "Frame/Frame/Frame.h"
#include "TextHandler/TextHandler.h"
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
        HexBuffer.push_back(HexIntVec[i]);
    }

    Frame framming(HexBuffer);
    framming.makeFrame();

    vector<int> frammedHex = framming.getFrame();
    for (int j = 0; j < frammedHex.size(); ++j) {
        cout << frammedHex[j];
    }

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

    return 0;
}
