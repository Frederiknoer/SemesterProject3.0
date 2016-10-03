#include <iostream>
#include <math.h>
#include <SFML/Audio.hpp>
#include "sound.h"
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

Sound::Sound() {

};


double Sound::tpc() {

    return 44100 / frequency;

}

double Sound::cycles() {

    return theTime/tpc();

}

double Sound::rad() {
#define TWOPI 6.283185
    return TWOPI * cycles();
}


short Sound::SinWave(double time, double freq, double amp) {

    theTime = time;
    frequency = freq;
    theAmplitude = amp * 32767;


    double result;
    return result = theAmplitude * sin(rad());

}


void Sound::playSound(vector<int> inputVector)
{


    int toneFirst[16] = {1209, 1336, 1447, 1633,
                         1209, 1336, 1447, 1633,
                         1209, 1336, 1447, 1633,
                         1209, 1336, 1447, 1633};

    int toneSecound[16] = {697, 697, 697, 697,
                           770, 770, 770, 770,
                           852, 852, 852, 852,
                           941, 941, 941, 941};


    int timePrTone = 500;

    sf::SoundBuffer bufferInput;
    vector<sf::Int16> inputSamples;


    for (int j = 0; j < inputVector.size(); ++j) {

        int tone = inputVector[j];
        int numberOfSamples = (44100 * timePrTone) / 1000; //44100 = the number of sampels for 1 sekund
        double fadeFirstLast = 0.1;
        double fadeInOut = 0.01;

        double setAmp = 1;  //0.0 - 1.0

        for (int i = 0; i < numberOfSamples; i++)
        {

// Fade in module

            if (j == 0)
            {
                if (i < (numberOfSamples * fadeFirstLast))
                {
                    inputSamples.push_back(
                            (SinWave(i, toneFirst[tone], (0.5 * setAmp) * (i / (numberOfSamples * fadeFirstLast)))) +
                            (SinWave(i, toneSecound[tone], (0.5 * setAmp) * (i / (numberOfSamples * fadeFirstLast)))));
                }
            }else{

                if (i < (numberOfSamples * fadeInOut))
                {
                    inputSamples.push_back(
                            (SinWave(i, toneFirst[tone], (0.5 * setAmp) * (i / (numberOfSamples * fadeInOut)))) +
                            (SinWave(i, toneSecound[tone], (0.5 * setAmp) * (i / (numberOfSamples * fadeInOut)))));
                }
            }

// No fadeing module

            if (j == 0)
            {
                if (((numberOfSamples * fadeFirstLast) < i) && (i < (numberOfSamples * (1 - fadeInOut))))
                {
                    inputSamples.push_back(
                            (SinWave(i, toneFirst[tone], (0.5 * setAmp))) +
                            (SinWave(i, toneSecound[tone], (0.5 * setAmp))));
                }

            }else{

                if( j == (inputVector.size() - 1) ){
                    if (((numberOfSamples * fadeInOut) < i) && (i < (numberOfSamples * (1 - fadeFirstLast)))) {
                        inputSamples.push_back(
                                (SinWave(i, toneFirst[tone], (0.5 * setAmp))) +
                                (SinWave(i, toneSecound[tone], (0.5 * setAmp))));
                    }
                }else {

                    if (((numberOfSamples * fadeInOut) < i) && (i < (numberOfSamples * (1 - fadeInOut)))) {
                        inputSamples.push_back(
                                (SinWave(i, toneFirst[tone], (0.5 * setAmp))) +
                                (SinWave(i, toneSecound[tone], (0.5 * setAmp))));
                    }
                }
            }


// Fade out module

            if (j == (inputVector.size() - 1) )
            {
                if (i > (numberOfSamples * (1-fadeFirstLast)))
                {
                    inputSamples.push_back(
                            (SinWave(i, toneFirst[tone], (0.5 * setAmp) * ((numberOfSamples - i) / (numberOfSamples * (fadeFirstLast))))) +
                            (SinWave(i, toneSecound[tone], (0.5 * setAmp) * ((numberOfSamples - i) / (numberOfSamples * (fadeFirstLast))))));
                }
            }else {

                if (i > (numberOfSamples * (1 - fadeInOut))) {
                    inputSamples.push_back(
                            (SinWave(i, toneFirst[tone],
                                     (0.5 * setAmp) * ((numberOfSamples - i) / (numberOfSamples * (fadeInOut))))) +
                            (SinWave(i, toneSecound[tone],
                                     (0.5 * setAmp) * ((numberOfSamples - i) / (numberOfSamples * (fadeInOut))))));
                }
            }
        }

    }

    bufferInput.loadFromSamples(&inputSamples[0], inputSamples.size(), 1, 44100);

    sf::Sound sound;
    sound.setBuffer(bufferInput);

    sound.play();
    delay(timePrTone*inputVector.size());

    cout << "Done playing sound" << endl;
}


void Sound::recordSound(int milli) {

    int ms = milli;
    cout << "Recording.. " << endl;
    if (!sf::SoundBufferRecorder::isAvailable()) {
        cout << "Audio device is uavalibale..." << endl;

        delay(ms);

    }

    sf::SoundBufferRecorder recorder;
    recorder.start();

    delay(ms);

    recorder.stop();

    const sf::SoundBuffer &buffer = recorder.getBuffer();

    sf::Sound soundOutput(buffer);
    soundOutput.play();

    cout << "Playing sound.." << endl;

    delay(ms);
}


void Sound::delay(int ms)
{


    #ifdef WINDOWS
    Sleep(ms);
    #else
    usleep(ms * 1000);
    #endif
}


Sound::~Sound() {

};