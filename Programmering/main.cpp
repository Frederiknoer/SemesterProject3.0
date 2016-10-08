#include <iostream>
#include <SFML/Audio.hpp>
#include "Sound/sound.h"
#include "TextHandler/TextHandler.h"
#include "Frame/Frame/Frame.h"
using namespace std;

int main()
{
    //Oprettelse af konstanter
    string inputText;
    vector<int> HexBuffer;
    vector<int> FrameBuffer;
    TextHandler dataIn;
    HexBuffer.clear();

    while(true) {
        //Læser input
        getline(cin, inputText);

        if (inputText == "stop")
            break;

        //Ligger teksten ind i HexBuffer som decimaler fra 0-15
        vector<int> HexIntVec = dataIn.InputText(inputText);
        for (int i = 0; i < (inputText.length() * 2); i++) {
            HexBuffer.push_back(HexIntVec[i]);
        }

        //Opretter frame objekt
        Frame framing(HexBuffer);
        framing.makeFrame();

        //Ligger hexbuffer ind i framebuffer med frame rundt om
        for (int i = 0; i < framing.getLength(); i++) {
            FrameBuffer.push_back(framing.getFrame().getElement(i));
        }

        //Afspiller lyd
        Sound SoundOne;
        SoundOne.playSound(FrameBuffer);

        //Tømmer bufferne
        HexBuffer.clear();
        HexIntVec.clear();
        FrameBuffer.clear();
    }
    return 0;
}