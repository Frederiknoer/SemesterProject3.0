#pragma once
#include <vector>
#include <iostream>

using namespace std;

class TextHandler
{
public:

	TextHandler();
	vector<int> InputText(string);
	string OutputText(vector<int>);
	~TextHandler();



private:

	//output consts.
	char outDataString[10000];
	vector<int> outputBuffer;

	vector<int> transNBuffer;
	vector<int> transBBuffer;

	//input conts.
	vector<int> inBuffer;
	vector<int> inputBuffer;
	unsigned char ucInCharacter;
	vector<char> inDataString;
};

