#include <iostream>
#include <array>
#include <vector>
#include "InputText.h"
using namespace std;

int main()
{
	//output consts.
	char outDataString[10000];
	vector<char> outputBuffer;

	//input conts.
	vector<int> inputBuffer;
	unsigned char ucInCharacter;
	char inDataString[10000];


	//output:
	cin.getline(outDataString, 10000);			//Reads input
	std::string str(outDataString);		

	for (int i = 0; i < str.length(); i++)		//Converts char's from the string to decimal(1 byte each), and saves them in the outputBuffer
	{
		unsigned char ucOutCharacter = (unsigned char)outDataString[i];
		outputBuffer[i] = (unsigned int)ucOutCharacter;
	}
	

	//input:
	for (int i = 0; i < str.length(); i++)		//Transfers the data from the outputBuffer to the inputBuffer
	{
		inputBuffer.push_back(outputBuffer[i]);
	}

	for (int i = 0; i < inputBuffer.size(); i++) //Converts decimals to chars and saves them in inDataString
	{
		ucInCharacter = (unsigned char)inputBuffer[i];
		inDataString[i] = ucInCharacter;
	}

	for (int i = 0; i < inputBuffer.size(); i++) //Writes out the input
	{
		cout << inDataString[i];
	}
	cout << endl;
    string ny;
    cin >> ny;
	return 0;

}

