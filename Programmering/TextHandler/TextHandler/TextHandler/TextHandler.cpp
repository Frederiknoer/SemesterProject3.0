#include "TextHandler.h"



TextHandler::TextHandler()
{
}

vector<int> TextHandler::InputText(vector<char> enC)
{
	outDataString = enC;

	for (int i = 0; i < outDataString.size(); i++)		//Converts char's from the string to decimal(1 byte each), and saves them in the outputBuffer
	{
		unsigned char ucOutCharacter = (unsigned char)outDataString[i];
		outputBuffer.push_back((unsigned int)ucOutCharacter);
	}

	return outputBuffer;
}

string TextHandler::OutputText(int enI)
{
	for (int i = 0; i < outputBuffer.size(); i++)		//Transfers the data from the outputBuffer to the inputBuffer
	{
		inputBuffer.push_back(outputBuffer[i]);
	}

	for (int i = 0; i < inputBuffer.size(); i++)		//Converts decimals to chars and saves them in inDataString
	{
		ucInCharacter = (unsigned char)inputBuffer[i];
		inDataString[i] = ucInCharacter;
	}
	
	for (int i = 0; i < inDataString.size(); i++)
	{
		if (i != 0)
		{
			ss << inDataString[i];
		}
		string s = ss.str();
	}

	return s;
}


TextHandler::~TextHandler()
{
}
