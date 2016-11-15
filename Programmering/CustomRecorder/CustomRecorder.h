#include <iostream>
#include "SFML/Audio.hpp"
#include "../DFT/DFT.h"
#include <chrono>
#include "../DtmfFinder.h"

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
};

