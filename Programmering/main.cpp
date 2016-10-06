#include <iostream>
#include <SFML/Audio.hpp>
#include "sound.h"

using namespace std;

int main()
{

    vector<int> toneInput;
    toneInput = {8, 4, 5, 10, 13, 0, 1, 6};

    Sound SoundOne;
    SoundOne.playSound(toneInput);

    /*
    Sound RecordSound;
    RecordSound.recordSound(5000);
    */
    int dontClose;
    cin >> dontClose;
    return 0;
}