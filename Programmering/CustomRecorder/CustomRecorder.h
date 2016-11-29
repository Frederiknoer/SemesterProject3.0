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
    void onStop();
	void resetRTS();
	void resetCTS();
	void resetACK();
	void resetDATA();
    ~CustomRecorder();

private:
	int index = 0;	// <=================== eksperimental

    DtmfFinder findTones;
    DtmfFinder lyddata;
    vector< vector<int> > udData;
	bool rtsFlag = 0;
	bool ctsFlag = 0;
	bool ackFlag = 0;
	bool dataFlag = 0;
	csmaCA csmaHandler;



};

