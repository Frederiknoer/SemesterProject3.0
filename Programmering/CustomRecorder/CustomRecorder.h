#include <iostream>
#include "SFML/Audio.hpp"
#include "../DFT/DFT.h"
#include <chrono>
#include "../DtmfFinder/DtmfFinder.h"
#include "../Frame/Frame/Frame.h"
#include "../TextHandler/TextHandler.h"
#include "../CSMAca/CSMAca/csmaCA.h"
#pragma once
using namespace std;

class CustomRecorder : public sf::SoundRecorder
{

public:
    CustomRecorder();
	CustomRecorder(csmaCA etO);
	csmaCA getcsmaCA();
    bool onStart();
    bool onProcessSamples(const sf::Int16 *samples, std::size_t sampleCount);
    void setSamplesPrDFT(int SamplesPerDTF);
    void onStop();
<<<<<<< HEAD
=======


>>>>>>> windowsTestEnvironment
    ~CustomRecorder();

private:
    DtmfFinder findTones;
    DtmfFinder lyddata;
    vector< vector<int> > udData;
<<<<<<< HEAD
	bool rtsFlag = 0;
	bool ctsFlag = 0;
	bool ackFlag = 0;
	bool dataFlag = 0;
	csmaCA csmaHandler;



=======
    vector<double> leftOverSamples;
    vector<double> dataToProcess;
    int samplesPrDFT;
>>>>>>> windowsTestEnvironment
};

