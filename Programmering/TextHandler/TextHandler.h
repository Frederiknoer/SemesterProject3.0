#pragma once
#include <vector>
#include <iostream>

using namespace std;

class TextHandler
{
public:

	TextHandler();
	vector<int> InputText(string);
	vector< vector<int> > textSplitter(vector<int>);
	vector<int> textAssembler(vector< vector<int> >);
	string OutputText(vector<int>);
	~TextHandler();



private:

	//output consts.
	char outDataString[10000];
	vector<int> outputBuffer;
	vector<int> transNBuffer;

	//input conts.
	string s;
};