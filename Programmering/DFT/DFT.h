#include <SFML/Audio.hpp>
#include <iostream>
#include <complex>

using namespace std;

#ifndef PROJEKT_DFT_H
#define PROJEKT_DFT_H


class DFT {
public:
    DFT();
    void DFTrans(const sf::Int16 *samples, double N, int sampleFreq);
    vector<double> getFreqSpek8();

    ~DFT();

private:
    vector<double> freqSpek;

};


#endif //PROJEKT_DFT_H
