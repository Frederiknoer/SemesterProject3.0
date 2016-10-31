#include <iostream>
#include "SFML/Audio.hpp"
#include "../DFT/DFT.h"
#include <chrono>

using namespace std;

class CustomRecorder : public sf::SoundRecorder
{

public:
    CustomRecorder();
    virtual bool onStart();
    virtual bool onProcessSamples(const sf::Int16 *samples, std::size_t sampleCount);
    void onStop();

    ~CustomRecorder();

public:


};

