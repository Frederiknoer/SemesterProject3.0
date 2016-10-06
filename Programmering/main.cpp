#include <iostream>
#include <SFML/Audio.hpp>
#include "Sound/sound.h"
#include "TextHandler/TextHandler.h"
#include "Frame/Frame/Frame.h"

using namespace std;

int main()
{

    string inputText;
    getline(cin, inputText);
    vector<int> HexBuffer;
    vector<int> FrameBuffer;
    TextHandler dataIn;
    HexBuffer.clear();


    for(int i = 0; i < (inputText.length() * 2); i++)
    {
        HexBuffer.push_back(dataIn.InputText(inputText)[i]);
    }

    Frame framing(HexBuffer);
    framing.makeFrame();

    for (int i = 0; i < framing.getLength(); i++)
    {
        FrameBuffer.push_back(framing.getFrame().getElement(i));
    }


    Sound SoundOne;
    SoundOne.playSound(FrameBuffer);

    /*
    Sound RecordSound;
    RecordSound.recordSound(5000);
    */

    Sound delayms;
    delayms.delay(2000);

}