#include <iostream>
#include "SFML/Audio.hpp"
#include "../DFT/DFT.h"
#include <chrono>
#include "../DtmfFinder/DtmfFinder.h"
#include "../Frame/Frame/Frame.h"
#include "../TextHandler/TextHandler.h"

using namespace std;

class CustomRecorder : public sf::SoundRecorder
{

public:
    CustomRecorder();
    bool onStart();
    bool onProcessSamples(const sf::Int16 *samples, std::size_t sampleCount);
    void onStop();


    ~CustomRecorder();

private:
    DtmfFinder findTones;
    DtmfFinder lyddata;
    vector< vector<int> > udData;
    vector<double> leftOverSamples;
    vector<double> dataToProcess;
    int counter = 0;
};

