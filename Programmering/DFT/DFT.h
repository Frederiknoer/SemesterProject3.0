#include <SFML/Audio.hpp>
#include <iostream>
#include <complex>

using namespace std;

#ifndef PROJEKT_DFT_H
#define PROJEKT_DFT_H


class DFT {
public:
    DFT();
    void DFTrans8(const sf::Int16 *samples, double N, int sampleFreq);
    void DFTrans(const sf::Int16 *samples, double N, int sampleFreq);
    void clearFreqSpek8();

    vector<double> getFreqSpek();
    vector<double> getFreqSpek8();

    ~DFT();

private:
    vector<double> freqSpek;

};


#endif //PROJEKT_DFT_H
