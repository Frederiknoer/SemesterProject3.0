#include "TextHandler.h"



TextHandler::TextHandler()
{
}

vector<int> TextHandler::InputText(string enS)
{
	for (int i = 0; i < enS.length(); i++)
	{
		outDataString[i] = enS[i];
	}
	string str(outDataString);

	for (int i = 0; i < str.length(); i++)		//Converts char's from the string to decimal(1 byte each), and saves them in the outputBuffer
	{
		unsigned char ucOutCharacter = (unsigned char)outDataString[i];
		outputBuffer.push_back((unsigned int)ucOutCharacter);
	}

	for (int i = 0; i < outputBuffer.size(); i++)
	{
		transNBuffer.push_back(outputBuffer[i] >> 4 & 0x0F);	//Shifts the 4 MSB's to LSB and masks out the 4 MSB and saves in the transBuffer
		transNBuffer.push_back(outputBuffer[i] & 0x0F);			//Masks out the 4 MSB's and saves in the transBuffer
	}

	return transNBuffer;
}

string TextHandler::OutputText(vector<int> vINT)
{
	inBuffer = vINT;

	for (int i = 0; i < (inBuffer.size()); i++)
	{
		int nibbleTransfer = (inBuffer[i + 1] | (inBuffer[i] << 4));
		transBBuffer.push_back(nibbleTransfer);
		i++;
	}

	for (int i = 0; i < transBBuffer.size(); i++)		//Transfers the data from the outputBuffer to the inputBuffer
	{
		inputBuffer.push_back(transBBuffer[i]);
	}

	for (int i = 0; i < inputBuffer.size(); i++)		//Converts decimals to chars and saves them in inDataString
	{
		ucInCharacter = (unsigned char)transBBuffer[i];
		inDataString[i] = ucInCharacter;
	}

	string s(inDataString.data(), inDataString.size());
	
	return s;
}




TextHandler::~TextHandler()
{
}
