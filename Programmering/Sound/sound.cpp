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



short Sound::sinWave(double time, double timePrTone, double freqLast, double freqNext) {


    double transformedFreqLast = freqLast/samplingRate;
    double transformedFreqNext = freqNext/samplingRate;

    return (short)(0.5*32767 * sin(TWOPI * (transformedFreqLast*timePrTone + time * transformedFreqNext)));
}


void Sound::makeSound(vector<int> inputVector)
{


    int toneFirst[16] = {1209, 1336, 1447, 1633,
                         1209, 1336, 1447, 1633,
                         1209, 1336, 1447, 1633,
                         1209, 1336, 1447, 1633};

    int toneSecound[16] = {697, 697, 697, 697,
                           770, 770, 770, 770,
                           852, 852, 852, 852,
                           941, 941, 941, 941};


    double timePrTone = 50;
    double numberOfSamples = (samplingRate * timePrTone) / 1000; //44100 = the number of sampels for 1 sekund
    double freqSumFirst = 0;
    double freqSumSecound = 0;

    vector <sf::Int16> bufferSamples;

    for (int j = 0; j < inputVector.size(); j++) {

        for (int i = 0; i < numberOfSamples; ++i){
            bufferSamples.push_back(
                    sinWave(i, numberOfSamples, freqSumFirst, toneFirst[inputVector[j]]) +
                    sinWave(i, numberOfSamples, freqSumSecound, toneSecound[inputVector[j]])
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