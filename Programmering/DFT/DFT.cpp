#include "DFT.h"

#define TWOPI 6.283185

DFT::DFT()
{
}


void DFT::DFTrans8(const sf::Int16 *samples, double N, int sampleFreq)
{

    double FreqFaktor = N/(sampleFreq);
    int FreqTabel[] = {697, 770, 852, 941, 1209, 1336, 1477, 1633};

    for (int k = 0; k < 8; k++) {

        complex<double> sum(0.0, 0.0);

        for (int j = 0; j <= N-1; j++) {
            int integers = -1 * j * FreqTabel[k];
            complex<double> exponent(0.0, (TWOPI * ((double) integers * FreqFaktor)) / N);
            sum += (double)1/N * samples[j] * exp(exponent);

        }
        freqSpek.push_back(abs(sum));
    }

}

void DFT::DFTrans(const sf::Int16 *samples, double N, int sampleFreq)
{

    double FreqFaktor = N/(sampleFreq);

    for (int k = 0; k < 2000; k++) {

        complex<double> sum(0.0, 0.0);

        for (int j = 0; j <= N-1; j++) {
            int integers = -1 * j * k;
            complex<double> exponent(0.0, (TWOPI * ((double) integers * FreqFaktor)) / N);
            sum += (double)1/N * samples[j] * exp(exponent);

        }
        freqSpek.push_back(abs(sum));
    }

}

vector<double> DFT::getFreqSpek8(){
    return freqSpek;
}

void DFT::clearFreqSpek8() {
    freqSpek.clear();
}

vector<double> DFT::getFreqSpek(){
    return freqSpek;
}

DFT::~DFT() {

}
