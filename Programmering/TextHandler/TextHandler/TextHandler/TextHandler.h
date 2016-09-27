#pragma once
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class TextHandler
{
public:

	TextHandler();
	vector<int> InputText(vector<char>);
	string OutputText(int);
	~TextHandler();

	//output consts.
	vector<char> outDataString;
	vector<int> outputBuffer;

	//input conts.
	vector<int> inputBuffer;
	unsigned char ucInCharacter;
	vector<char> inDataString;

	stringstream ss;
	string s;

private:

};

