#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Sound/sound.h"
#include "TextHandler/TextHandler.h"
#include "CustomRecorder/CustomRecorder.h"
using namespace std;


int main()
{
    unsigned int recordSampleRate = 96000;
    unsigned int playSampleRate = 44100;

    Sound mySound;
    mySound.setSamplingRate(playSampleRate);

    CustomRecorder recorder;
    recorder.start(recordSampleRate);

    string mystring;
    cout << "Skriv tekst: ";
    cin >> mystring;

while (1) {
    vector<int> HexBuffer = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};


    /*
    TextHandler myTest;
    vector<int> HexIntVec = myTest.InputText(mystring);

    for (int i = 0; i < (mystring.length() * 2); ++i) {
        HexBuffer.push_back(HexIntVec[i]);
    }
     */


    mySound.makeSound(HexBuffer);


    vector<sf::Int16> inputSamples = mySound.getSound();

    sf::SoundBuffer bufferInput;
    bufferInput.loadFromSamples(&inputSamples[0], inputSamples.size(), 1, playSampleRate);

    sf::Sound sound;
    sound.setBuffer(bufferInput);
    sound.play();

    HexBuffer.clear();
//    HexIntVec.clear();


    cout << "Skriv tekst: ";
    cin >> mystring;



}

    recorder.stop();

    return 0;
}
