#include <iostream>
#include <SFML/Audio.hpp>
#include "sound.h"
#include "TextHandler.h"

using namespace std;

int main()
{

    string inputText;
    getline(cin, inputText);
    vector<int> HexBuffer;

    TextHandler dataIn;
    for (int i = 0; i < (inputText.length() * 2); i++)
    {
        HexBuffer.push_back(dataIn.InputText(inputText)[i]);
    }

    Sound SoundOne;
    SoundOne.playSound(HexBuffer);

    /*
    Sound RecordSound;
    RecordSound.recordSound(5000);
    */

    Sound delayms;
    delayms.delay(2000);

}