#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Sound/sound.h"
#include "TextHandler/TextHandler.h"
#include "Frame/Frame/Frame.h"
#include <complex>
#include <math.h>
using namespace std;


int main()
{

    int samplingFreq = 44100;
    int dt = 1/samplingFreq;
    double recordTime = 1;
    int z = -1;


    sf::SoundBufferRecorder recorder;
    recorder.start();

    cout << "Recording.." << endl;
    Sound delayms;
    delayms.delay(recordTime);
    cout << "Done Recording" << endl;

    recorder.stop();

    double NumSamp = 44100 * (recordTime/1000);
    cout << NumSamp << endl;

    const sf::SoundBuffer& buffer = recorder.getBuffer();
    const sf::Int16 *samples = buffer.getSamples();

    vector<int> freqData;

    for (int i = 0; i < 200; i++)
    {
        double Data = 0;
        for (int j = 0; j < NumSamp; j++)
        {
            Data = Data +  ( exp(real(z) * ((2 * M_PI) / NumSamp) * i * j));
        }
        freqData.push_back(Data);
        cout << Data << endl;

    }

    double long vectorSize = freqData.size();
    cout << vectorSize << endl;

    return 0;

}


/*
int main()
{
    //Oprettelse af konstanter
    string inputText;
    vector<int> HexBuffer;
    vector<int> FrameBuffer;
    TextHandler dataIn;
    HexBuffer.clear();

    while(true) {
        //Læser input
        getline(cin, inputText);

        if (inputText == "stop")
            break;

        //Ligger teksten ind i HexBuffer som decimaler fra 0-15
        vector<int> HexIntVec = dataIn.InputText(inputText);
        for (int i = 0; i < (inputText.length() * 2); i++) {
            HexBuffer.push_back(HexIntVec[i]);
        }

        //Opretter frame objekt
        Frame framing(HexBuffer);
        framing.makeFrame();

        //Ligger hexbuffer ind i framebuffer med frame rundt om
        for (int i = 0; i < framing.getLength(); i++) {
            FrameBuffer.push_back(framing.getFrame().getElement(i));
        }

        //Afspiller lyd
        Sound SoundOne;
        SoundOne.playSound(FrameBuffer);

        //Tømmer bufferne
        HexBuffer.clear();
        HexIntVec.clear();
        FrameBuffer.clear();
    }
    return 0;
}

 */