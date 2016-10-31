#include "DFT.h"

DFT::DFT()
{
}


void DFT::DFTrans(const sf::Int16 *samples, double N, int sampleFreq)
{

    double FreqFaktor = N/(sampleFreq);
    int FreqTabel[] = {697, 770, 852, 941, 1209, 1336, 1477, 1633};

    for (int k = 0; k < 8; k++) {

        complex<double> sum(0.0, 0.0);

        for (int j = 0; j <= N-1; j++) {
            int integers = -2 * j * FreqTabel[k];
            complex<double> exponent(0.0, (M_PI * ((double) integers * FreqFaktor)) / N);
            sum += (double) samples[j] * exp(exponent);

        }
        freqSpek.push_back(abs(sum));
    }

}

vector<double> DFT::getFreqSpek8(){
    return freqSpek;
}


DFT::~DFT() {

}
