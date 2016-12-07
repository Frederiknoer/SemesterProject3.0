#include "TextHandler.h"


TextHandler::TextHandler()
{
}

vector<int> TextHandler::InputText(string enS)
{
	vector<char> outDataString;
	vector<int> outputBuffer;
	vector<int> transNBuffer;
	transNBuffer.clear();
	outDataString.clear();
	outputBuffer.clear;

	for (int i = 0; i < enS.length(); i++)
	{
		outDataString.push_back(enS[i]);
		outputBuffer.push_back((unsigned int)((unsigned char)outDataString[i]));
		transNBuffer.push_back(outputBuffer[i] >> 4 & 0x0F);	//Shifts the 4 MSB's to LSB and masks out the 4 MSB and saves in the transBuffer
		transNBuffer.push_back(outputBuffer[i] & 0x0F);			//Masks out the 4 MSB's and saves in the transBuffer
	}
	return transNBuffer;
}

vector< vector<int> > TextHandler::textSplitter(vector<int> textVec)
{
	int splitCounter = 8;
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
			//cout << textVec[(j + (counter*splitCounter))] << ", ";
		}
		//cout << endl;
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
			//cout << textVec[i] << ", ";
		}
		//cout << endl;
		hexBuffer.push_back(rowMaker);
		rowMaker.clear();
	}
	//cout << hexBuffer.back().back();
	hexBuffer.push_back(endPackage);

	//cout << endl << hexBuffer.size();
	return hexBuffer;
}

vector<int> TextHandler::textAssembler(vector <vector<int> > packageVec)
{
	int packageNumber = 0;
	vector<int> AssembletHex;
	//cout << packageVec.size() << endl;
	for (int i = 0; i < packageVec.size(); i++)
	{
		if (packageNumber > 15)
		{
			packageNumber = 0;
		}

		if (packageNumber == (packageVec[i][0])) {
			packageVec[i].erase(packageVec[i].begin());
			for (int j = 0; j < packageVec[i].size(); j++)
			{
				AssembletHex.push_back(packageVec[i][j]);
				//cout << packageVec[i][j] << ", ";
			}
			//cout << endl;
			packageNumber++;
		}
		else
		{
			packageVec.erase(packageVec.begin());
			i--;
		}

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