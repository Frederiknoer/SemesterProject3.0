#include <iostream>
#include <string>
#include <array>
#include <vector>
using namespace std;

int main()
{
	//output consts.
	char outDataString[10000];
	int outputBuffer[10000];

	//input conts.
	vector<int> inputBuffer;
	unsigned char ucInCharacter;
	char inDataString[10000];


	//output:
	cin.getline(outDataString, 10000);			//Reads input
	std::string str(outDataString);		

	for (int i = 0; i < str.length(); i++)		//Converts char's from the string to decimal(1 byte each), and saves them in the outputBuffer
	{
		unsigned char ucOutCharacter = outDataString[i];
		outputBuffer[i] = (unsigned int)ucOutCharacter;
	}
	

	//input:
	for (int i = 0; i < str.length(); i++)		//Transfers the data from the outputBuffer to the inputBuffer
	{
		inputBuffer.push_back(outputBuffer[i]);
	}

	for (int i = 0; i < inputBuffer.size(); i++) //Converts decimals to chars and saves them in inDataString
	{
		(unsigned char)ucInCharacter = inputBuffer[i];
		inDataString[i] = ucInCharacter;
	}

	for (int i = 0; i < inputBuffer.size(); i++) //Writes out the input
	{
		cout << inDataString[i];
	}
	cout << endl;

	return 0;

}

