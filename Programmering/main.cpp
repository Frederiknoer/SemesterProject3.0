#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Sound/sound.h"
#include "TextHandler/TextHandler.h"
#include "CustomRecorder/CustomRecorder.h"
using namespace std;

#define TWOPI = 6.283185

int main()
{
    unsigned int recordSampleRate = 4096;
    unsigned int playSampleRate = 44100;

    Sound mySound;
    mySound.setSamplingRate(playSampleRate);

    CustomRecorder recorder;
    recorder.start(recordSampleRate);

    mySound.delay(2000);


    //string mystring;
    //cout << "Skriv tekst: ";
    //getline(cin, mystring);

/*while (1) {
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
} */


    recorder.stop();

    return 0;
}
