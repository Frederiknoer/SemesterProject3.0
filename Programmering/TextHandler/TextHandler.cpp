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

vector< vector<int> > TextHandler::textSplitter(vector<int> textVec)
{
	int splitCounter = 6;
	vector<int> rowMaker;
	vector< vector<int> > hexBuffer;
	hexBuffer.clear();
	int counter = 0;
	int packageNumber = 0;
	vector<int> endPackage = { 1, 15, 1, 15 };

	for (int i = 0; i < (textVec.size()/splitCounter); i++)
	{
		rowMaker.push_back(packageNumber);
		for (int j = 0; j < splitCounter; j++)
		{
			rowMaker.push_back(textVec[(j + (counter*splitCounter))]);
		}
		hexBuffer.push_back(rowMaker);
		counter++;
		packageNumber++;
		rowMaker.clear();
		if (packageNumber > 15)
			packageNumber = 0;
	}
	if (textVec.size() % splitCounter > 0)
	{
		rowMaker.push_back(packageNumber);
		for (int i = (counter*splitCounter); i < textVec.size(); i++)
		{
			rowMaker.push_back(textVec[i]);
		}
		hexBuffer.push_back(rowMaker);
		rowMaker.clear();
	}
	//cout << hexBuffer.back().back();
	hexBuffer.push_back(endPackage);

	return hexBuffer;
}

vector<int> TextHandler::textAssembler(vector <vector<int> > packageVec)
{
	int packageNumber = 0;
	int packageIndex = 0;
	vector<int> AssembletHex;

	for (int i = 0; i < packageVec.size(); i++)
	{
		if (packageNumber > 15)
		{
			packageNumber = 0;
			packageIndex = packageIndex - 16;
		}

		if (packageNumber == (packageVec[i][0] + (1 * packageIndex))) {
			packageVec[i].erase(packageVec[i].begin());
			for (int j = 0; j < packageVec[i].size(); j++) {
				AssembletHex.push_back(packageVec[i][j]);
			}
			packageNumber++;
		}
		else
			packageVec.erase(packageVec.begin());
	}
	return AssembletHex;
}

string TextHandler::OutputText(vector<int> vecInt)
{
	vector<char> inDataString;

	for (int i = 0; i < vecInt.size(); i += 2)
	{
		int nibbleTransfer = (vecInt[i + 1] | (vecInt[i] << 4));
		inDataString.push_back((unsigned char)nibbleTransfer);
	}

	string s(inDataString.data(), inDataString.size());

	return s;
}


TextHandler::~TextHandler()
{
}