#include <iostream>
#include <math.h>
#include <SFML/Audio.hpp>
#include "sound.h"

#define TWOPI 6.283185

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <unistd.h>
#endif


Sound::Sound() {

};

void Sound::setSamplingRate(double SR) {
    samplingRate = SR;
}

short Sound::sinWave(double amp, double time, double timePrTone, int freqLast, int freqNext) {


    double transformedFreqLast = freqLast/samplingRate;
    double transformedFreqNext = freqNext/samplingRate;

    return (short)(amp * 32767 * cos(TWOPI * (transformedFreqLast*timePrTone + time * transformedFreqNext)));
}

short Sound::sinWaveOld(double amp, double time, int freq) {
    return (short)(amp * 32767 * cos(TWOPI * (freq/samplingRate) * time));
}


void Sound::makeSound(vector<int> inputVector)
{


    int toneFirst[16] = {1209, 1336, 1447, 1633,
                         1209, 1336, 1447, 1633,
                         1209, 1336, 1447, 1633,
                         1209, 1336, 1447, 1633};

    double freqFirst[16] = {0.7, 0.95, 0.7, 0.9,
                            0.7, 0.95, 0.7, 0.9,
                            0.7, 0.95, 0.7, 0.9,
                            0.7, 0.95, 0.7, 0.9};

    int toneSecound[16] = {697, 697, 697, 697,
                           770, 770, 770, 770,
                           852, 852, 852, 852,
                           941, 941, 941, 941};

    double freqSecound[16] = {1, 1, 1, 1,
                           1, 1, 1, 1,
                           1, 1, 1, 1,
                           1, 1, 1, 1};
    int numberOfSamples = samplesPrTone * (samplingRate/4096);
    int freqSumFirst = 0;
    int freqSumSecound = 0;
    double amplitude = 0.5;


    vector <sf::Int16> bufferSamples;

    for (int j = 0; j < inputVector.size(); j++) {

        for (int i = 0; i < numberOfSamples; ++i){

            bufferSamples.push_back(
                    sinWave(amplitude, i, numberOfSamples, freqSumFirst, toneFirst[inputVector[j]]) +
                    sinWave(amplitude,  i, numberOfSamples, freqSumSecound, toneSecound[inputVector[j]])
            );

        }
        freqSumFirst = freqSumFirst + toneFirst[inputVector[j]];
        freqSumSecound = freqSumSecound + toneSecound[inputVector[j]];
    }

    inputSamples = bufferSamples;
}


vector<sf::Int16> Sound::getSound() {
    return inputSamples;
}

void Sound::setSamplePrTone(int samplePlayTime) {
    samplesPrTone = samplePlayTime;
}

void Sound::delay(double ms)
{

#ifdef __APPLE__
    usleep((useconds_t )ms * 1000);
#endif

#ifdef _WIN32
    Sleep(ms);
#endif


}


Sound::~Sound() {

};
