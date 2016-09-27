#include <iostream>
#include <array>
#include <vector>

using namespace std;

int main()
{
	//output consts.
	char outDataString[10000];
	vector<char> outputBuffer;
	vector<int> transNBuffer;
	vector<char> transBBuffer;

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
		outputBuffer.push_back((unsigned int)ucOutCharacter);
	}

	//Seperator from bytes to nibbles
	for (int i = 0; i < outputBuffer.size(); i++)
	{
		transNBuffer.push_back(outputBuffer[i] >> 4 & 0x0F);	//Shifts the 4 MSB's to LSB and masks out the 4 MSB and saves in the transBuffer
		transNBuffer.push_back(outputBuffer[i] & 0x0F);		//Masks out the 4 MSB's and saves in the transBuffer
	}
	

	//input:

	//Assembles nibbles to bytes
	for (int i = 0; i < (transNBuffer.size()); i++)
	{
		int nibbleTransfer = (transNBuffer[i + 1] | (transNBuffer[i] << 4));
		transBBuffer.push_back(nibbleTransfer);
		i++;
	}

	for (int i = 0; i < transBBuffer.size(); i++)		//Transfers the data from the outputBuffer to the inputBuffer
	{
		inputBuffer.push_back(transBBuffer[i]);
	}

	for (int i = 0; i < inputBuffer.size(); i++)		//Converts decimals to chars and saves them in inDataString
	{
		ucInCharacter = (unsigned char)inputBuffer[i];
		inDataString[i] = ucInCharacter;
	}

	for (int i = 0; i < inputBuffer.size(); i++)		//Writes out the input
	{
		cout << inDataString[i];
	}
	cout << endl;





	return 0;

}

